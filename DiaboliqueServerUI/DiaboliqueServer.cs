using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;

namespace DiaboliqueServerUI
{
    static class DiaboliqueServer
    {

        [DllImport("DiaboliqueServer.dll", CharSet = CharSet.Ansi,
         CallingConvention = CallingConvention.StdCall)]
        [return: MarshalAs(UnmanagedType.BStr)]
       public static extern string GetConnectionName(int nIndex);

        [DllImport("DiaboliqueServer.dll", CallingConvention = CallingConvention.StdCall)]
        public static extern IntPtr Get_Diabolique_Server();

        [DllImport("DiaboliqueServer.dll", CallingConvention = CallingConvention.StdCall)]
        public static extern int GetClientCount();

        [DllImport("DiaboliqueServer.dll")]
        private static extern void GetClients(out int length, out IntPtr array);

        public static void GetClientsWrap(ref int[] theArray)
        {
            int theSize;
            IntPtr theArrayPtr;

            GetClients(out theSize, out theArrayPtr);
            Marshal.Copy(theArrayPtr, theArray, 0, theSize);
            //Marshal.FreeCoTaskMem(theArrayPtr);
        }

    }
}
