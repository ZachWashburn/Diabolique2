// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: google/protobuf/unittest_preserve_unknown_enum2.proto

#include "google/protobuf/unittest_preserve_unknown_enum2.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG

namespace _pb = ::PROTOBUF_NAMESPACE_ID;
namespace _pbi = _pb::internal;

namespace proto2_preserve_unknown_enum_unittest {
PROTOBUF_CONSTEXPR MyMessage::MyMessage(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_._has_bits_)*/{}
  , /*decltype(_impl_._cached_size_)*/{}
  , /*decltype(_impl_.repeated_e_)*/{}
  , /*decltype(_impl_.repeated_packed_e_)*/{}
  , /*decltype(_impl_._repeated_packed_e_cached_byte_size_)*/{0}
  , /*decltype(_impl_.repeated_packed_unexpected_e_)*/{}
  , /*decltype(_impl_.e_)*/0
  , /*decltype(_impl_.o_)*/{}
  , /*decltype(_impl_._oneof_case_)*/{}} {}
struct MyMessageDefaultTypeInternal {
  PROTOBUF_CONSTEXPR MyMessageDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~MyMessageDefaultTypeInternal() {}
  union {
    MyMessage _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 MyMessageDefaultTypeInternal _MyMessage_default_instance_;
}  // namespace proto2_preserve_unknown_enum_unittest
static ::_pb::Metadata file_level_metadata_google_2fprotobuf_2funittest_5fpreserve_5funknown_5fenum2_2eproto[1];
static const ::_pb::EnumDescriptor* file_level_enum_descriptors_google_2fprotobuf_2funittest_5fpreserve_5funknown_5fenum2_2eproto[1];
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_google_2fprotobuf_2funittest_5fpreserve_5funknown_5fenum2_2eproto = nullptr;

const uint32_t TableStruct_google_2fprotobuf_2funittest_5fpreserve_5funknown_5fenum2_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  PROTOBUF_FIELD_OFFSET(::proto2_preserve_unknown_enum_unittest::MyMessage, _impl_._has_bits_),
  PROTOBUF_FIELD_OFFSET(::proto2_preserve_unknown_enum_unittest::MyMessage, _internal_metadata_),
  ~0u,  // no _extensions_
  PROTOBUF_FIELD_OFFSET(::proto2_preserve_unknown_enum_unittest::MyMessage, _impl_._oneof_case_[0]),
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  ~0u,  // no _split_
  ~0u,  // no sizeof(Split)
  PROTOBUF_FIELD_OFFSET(::proto2_preserve_unknown_enum_unittest::MyMessage, _impl_.e_),
  PROTOBUF_FIELD_OFFSET(::proto2_preserve_unknown_enum_unittest::MyMessage, _impl_.repeated_e_),
  PROTOBUF_FIELD_OFFSET(::proto2_preserve_unknown_enum_unittest::MyMessage, _impl_.repeated_packed_e_),
  PROTOBUF_FIELD_OFFSET(::proto2_preserve_unknown_enum_unittest::MyMessage, _impl_.repeated_packed_unexpected_e_),
  ::_pbi::kInvalidFieldOffsetTag,
  ::_pbi::kInvalidFieldOffsetTag,
  PROTOBUF_FIELD_OFFSET(::proto2_preserve_unknown_enum_unittest::MyMessage, _impl_.o_),
  0,
  ~0u,
  ~0u,
  ~0u,
  ~0u,
  ~0u,
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 15, -1, sizeof(::proto2_preserve_unknown_enum_unittest::MyMessage)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::proto2_preserve_unknown_enum_unittest::_MyMessage_default_instance_._instance,
};

const char descriptor_table_protodef_google_2fprotobuf_2funittest_5fpreserve_5funknown_5fenum2_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n5google/protobuf/unittest_preserve_unkn"
  "own_enum2.proto\022%proto2_preserve_unknown"
  "_enum_unittest\"\270\003\n\tMyMessage\0228\n\001e\030\001 \001(\0162"
  "-.proto2_preserve_unknown_enum_unittest."
  "MyEnum\022A\n\nrepeated_e\030\002 \003(\0162-.proto2_pres"
  "erve_unknown_enum_unittest.MyEnum\022L\n\021rep"
  "eated_packed_e\030\003 \003(\0162-.proto2_preserve_u"
  "nknown_enum_unittest.MyEnumB\002\020\001\022S\n\034repea"
  "ted_packed_unexpected_e\030\004 \003(\0162-.proto2_p"
  "reserve_unknown_enum_unittest.MyEnum\022B\n\t"
  "oneof_e_1\030\005 \001(\0162-.proto2_preserve_unknow"
  "n_enum_unittest.MyEnumH\000\022B\n\toneof_e_2\030\006 "
  "\001(\0162-.proto2_preserve_unknown_enum_unitt"
  "est.MyEnumH\000B\003\n\001o*#\n\006MyEnum\022\007\n\003FOO\020\000\022\007\n\003"
  "BAR\020\001\022\007\n\003BAZ\020\002"
  ;
static ::_pbi::once_flag descriptor_table_google_2fprotobuf_2funittest_5fpreserve_5funknown_5fenum2_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_google_2fprotobuf_2funittest_5fpreserve_5funknown_5fenum2_2eproto = {
    false, false, 574, descriptor_table_protodef_google_2fprotobuf_2funittest_5fpreserve_5funknown_5fenum2_2eproto,
    "google/protobuf/unittest_preserve_unknown_enum2.proto",
    &descriptor_table_google_2fprotobuf_2funittest_5fpreserve_5funknown_5fenum2_2eproto_once, nullptr, 0, 1,
    schemas, file_default_instances, TableStruct_google_2fprotobuf_2funittest_5fpreserve_5funknown_5fenum2_2eproto::offsets,
    file_level_metadata_google_2fprotobuf_2funittest_5fpreserve_5funknown_5fenum2_2eproto, file_level_enum_descriptors_google_2fprotobuf_2funittest_5fpreserve_5funknown_5fenum2_2eproto,
    file_level_service_descriptors_google_2fprotobuf_2funittest_5fpreserve_5funknown_5fenum2_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_google_2fprotobuf_2funittest_5fpreserve_5funknown_5fenum2_2eproto_getter() {
  return &descriptor_table_google_2fprotobuf_2funittest_5fpreserve_5funknown_5fenum2_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_google_2fprotobuf_2funittest_5fpreserve_5funknown_5fenum2_2eproto(&descriptor_table_google_2fprotobuf_2funittest_5fpreserve_5funknown_5fenum2_2eproto);
namespace proto2_preserve_unknown_enum_unittest {
const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* MyEnum_descriptor() {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_google_2fprotobuf_2funittest_5fpreserve_5funknown_5fenum2_2eproto);
  return file_level_enum_descriptors_google_2fprotobuf_2funittest_5fpreserve_5funknown_5fenum2_2eproto[0];
}
bool MyEnum_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
      return true;
    default:
      return false;
  }
}


// ===================================================================

class MyMessage::_Internal {
 public:
  using HasBits = decltype(std::declval<MyMessage>()._impl_._has_bits_);
  static constexpr int32_t kHasBitsOffset =
    8 * PROTOBUF_FIELD_OFFSET(MyMessage, _impl_._has_bits_);
  static constexpr int32_t kOneofCaseOffset =
    PROTOBUF_FIELD_OFFSET(::proto2_preserve_unknown_enum_unittest::MyMessage, _impl_._oneof_case_);
  static void set_has_e(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
};

MyMessage::MyMessage(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:proto2_preserve_unknown_enum_unittest.MyMessage)
}
MyMessage::MyMessage(const MyMessage& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  MyMessage* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_._has_bits_){from._impl_._has_bits_}
    , /*decltype(_impl_._cached_size_)*/{}
    , decltype(_impl_.repeated_e_){from._impl_.repeated_e_}
    , decltype(_impl_.repeated_packed_e_){from._impl_.repeated_packed_e_}
    , /*decltype(_impl_._repeated_packed_e_cached_byte_size_)*/{0}
    , decltype(_impl_.repeated_packed_unexpected_e_){from._impl_.repeated_packed_unexpected_e_}
    , decltype(_impl_.e_){}
    , decltype(_impl_.o_){}
    , /*decltype(_impl_._oneof_case_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _this->_impl_.e_ = from._impl_.e_;
  clear_has_o();
  switch (from.o_case()) {
    case kOneofE1: {
      _this->_internal_set_oneof_e_1(from._internal_oneof_e_1());
      break;
    }
    case kOneofE2: {
      _this->_internal_set_oneof_e_2(from._internal_oneof_e_2());
      break;
    }
    case O_NOT_SET: {
      break;
    }
  }
  // @@protoc_insertion_point(copy_constructor:proto2_preserve_unknown_enum_unittest.MyMessage)
}

inline void MyMessage::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_._has_bits_){}
    , /*decltype(_impl_._cached_size_)*/{}
    , decltype(_impl_.repeated_e_){arena}
    , decltype(_impl_.repeated_packed_e_){arena}
    , /*decltype(_impl_._repeated_packed_e_cached_byte_size_)*/{0}
    , decltype(_impl_.repeated_packed_unexpected_e_){arena}
    , decltype(_impl_.e_){0}
    , decltype(_impl_.o_){}
    , /*decltype(_impl_._oneof_case_)*/{}
  };
  clear_has_o();
}

MyMessage::~MyMessage() {
  // @@protoc_insertion_point(destructor:proto2_preserve_unknown_enum_unittest.MyMessage)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void MyMessage::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.repeated_e_.~RepeatedField();
  _impl_.repeated_packed_e_.~RepeatedField();
  _impl_.repeated_packed_unexpected_e_.~RepeatedField();
  if (has_o()) {
    clear_o();
  }
}

void MyMessage::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void MyMessage::clear_o() {
// @@protoc_insertion_point(one_of_clear_start:proto2_preserve_unknown_enum_unittest.MyMessage)
  switch (o_case()) {
    case kOneofE1: {
      // No need to clear
      break;
    }
    case kOneofE2: {
      // No need to clear
      break;
    }
    case O_NOT_SET: {
      break;
    }
  }
  _impl_._oneof_case_[0] = O_NOT_SET;
}


void MyMessage::Clear() {
// @@protoc_insertion_point(message_clear_start:proto2_preserve_unknown_enum_unittest.MyMessage)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.repeated_e_.Clear();
  _impl_.repeated_packed_e_.Clear();
  _impl_.repeated_packed_unexpected_e_.Clear();
  _impl_.e_ = 0;
  clear_o();
  _impl_._has_bits_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* MyMessage::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // optional .proto2_preserve_unknown_enum_unittest.MyEnum e = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          uint64_t val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
          if (PROTOBUF_PREDICT_TRUE(::proto2_preserve_unknown_enum_unittest::MyEnum_IsValid(val))) {
            _internal_set_e(static_cast<::proto2_preserve_unknown_enum_unittest::MyEnum>(val));
          } else {
            ::PROTOBUF_NAMESPACE_ID::internal::WriteVarint(1, val, mutable_unknown_fields());
          }
        } else
          goto handle_unusual;
        continue;
      // repeated .proto2_preserve_unknown_enum_unittest.MyEnum repeated_e = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 16)) {
          ptr -= 1;
          do {
            ptr += 1;
            uint64_t val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
            CHK_(ptr);
            if (PROTOBUF_PREDICT_TRUE(::proto2_preserve_unknown_enum_unittest::MyEnum_IsValid(val))) {
              _internal_add_repeated_e(static_cast<::proto2_preserve_unknown_enum_unittest::MyEnum>(val));
            } else {
              ::PROTOBUF_NAMESPACE_ID::internal::WriteVarint(2, val, mutable_unknown_fields());
            }
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<16>(ptr));
        } else if (static_cast<uint8_t>(tag) == 18) {
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::PackedEnumParser<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(_internal_mutable_repeated_e(), ptr, ctx, ::proto2_preserve_unknown_enum_unittest::MyEnum_IsValid, &_internal_metadata_, 2);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // repeated .proto2_preserve_unknown_enum_unittest.MyEnum repeated_packed_e = 3 [packed = true];
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 26)) {
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::PackedEnumParser<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(_internal_mutable_repeated_packed_e(), ptr, ctx, ::proto2_preserve_unknown_enum_unittest::MyEnum_IsValid, &_internal_metadata_, 3);
          CHK_(ptr);
        } else if (static_cast<uint8_t>(tag) == 24) {
          uint64_t val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
          if (PROTOBUF_PREDICT_TRUE(::proto2_preserve_unknown_enum_unittest::MyEnum_IsValid(val))) {
            _internal_add_repeated_packed_e(static_cast<::proto2_preserve_unknown_enum_unittest::MyEnum>(val));
          } else {
            ::PROTOBUF_NAMESPACE_ID::internal::WriteVarint(3, val, mutable_unknown_fields());
          }
        } else
          goto handle_unusual;
        continue;
      // repeated .proto2_preserve_unknown_enum_unittest.MyEnum repeated_packed_unexpected_e = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 32)) {
          ptr -= 1;
          do {
            ptr += 1;
            uint64_t val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
            CHK_(ptr);
            if (PROTOBUF_PREDICT_TRUE(::proto2_preserve_unknown_enum_unittest::MyEnum_IsValid(val))) {
              _internal_add_repeated_packed_unexpected_e(static_cast<::proto2_preserve_unknown_enum_unittest::MyEnum>(val));
            } else {
              ::PROTOBUF_NAMESPACE_ID::internal::WriteVarint(4, val, mutable_unknown_fields());
            }
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<32>(ptr));
        } else if (static_cast<uint8_t>(tag) == 34) {
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::PackedEnumParser<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(_internal_mutable_repeated_packed_unexpected_e(), ptr, ctx, ::proto2_preserve_unknown_enum_unittest::MyEnum_IsValid, &_internal_metadata_, 4);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // .proto2_preserve_unknown_enum_unittest.MyEnum oneof_e_1 = 5;
      case 5:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 40)) {
          uint64_t val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
          if (PROTOBUF_PREDICT_TRUE(::proto2_preserve_unknown_enum_unittest::MyEnum_IsValid(val))) {
            _internal_set_oneof_e_1(static_cast<::proto2_preserve_unknown_enum_unittest::MyEnum>(val));
          } else {
            ::PROTOBUF_NAMESPACE_ID::internal::WriteVarint(5, val, mutable_unknown_fields());
          }
        } else
          goto handle_unusual;
        continue;
      // .proto2_preserve_unknown_enum_unittest.MyEnum oneof_e_2 = 6;
      case 6:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 48)) {
          uint64_t val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
          if (PROTOBUF_PREDICT_TRUE(::proto2_preserve_unknown_enum_unittest::MyEnum_IsValid(val))) {
            _internal_set_oneof_e_2(static_cast<::proto2_preserve_unknown_enum_unittest::MyEnum>(val));
          } else {
            ::PROTOBUF_NAMESPACE_ID::internal::WriteVarint(6, val, mutable_unknown_fields());
          }
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  _impl_._has_bits_.Or(has_bits);
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* MyMessage::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:proto2_preserve_unknown_enum_unittest.MyMessage)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _impl_._has_bits_[0];
  // optional .proto2_preserve_unknown_enum_unittest.MyEnum e = 1;
  if (cached_has_bits & 0x00000001u) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteEnumToArray(
      1, this->_internal_e(), target);
  }

  // repeated .proto2_preserve_unknown_enum_unittest.MyEnum repeated_e = 2;
  for (int i = 0, n = this->_internal_repeated_e_size(); i < n; i++) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteEnumToArray(
        2, this->_internal_repeated_e(i), target);
  }

  // repeated .proto2_preserve_unknown_enum_unittest.MyEnum repeated_packed_e = 3 [packed = true];
  {
    int byte_size = _impl_._repeated_packed_e_cached_byte_size_.Get();
    if (byte_size > 0) {
      target = stream->WriteEnumPacked(
          3, _impl_.repeated_packed_e_, byte_size, target);
    }
  }

  // repeated .proto2_preserve_unknown_enum_unittest.MyEnum repeated_packed_unexpected_e = 4;
  for (int i = 0, n = this->_internal_repeated_packed_unexpected_e_size(); i < n; i++) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteEnumToArray(
        4, this->_internal_repeated_packed_unexpected_e(i), target);
  }

  switch (o_case()) {
    case kOneofE1: {
      target = stream->EnsureSpace(target);
      target = ::_pbi::WireFormatLite::WriteEnumToArray(
        5, this->_internal_oneof_e_1(), target);
      break;
    }
    case kOneofE2: {
      target = stream->EnsureSpace(target);
      target = ::_pbi::WireFormatLite::WriteEnumToArray(
        6, this->_internal_oneof_e_2(), target);
      break;
    }
    default: ;
  }
  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:proto2_preserve_unknown_enum_unittest.MyMessage)
  return target;
}

size_t MyMessage::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:proto2_preserve_unknown_enum_unittest.MyMessage)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated .proto2_preserve_unknown_enum_unittest.MyEnum repeated_e = 2;
  {
    size_t data_size = 0;
    unsigned int count = static_cast<unsigned int>(this->_internal_repeated_e_size());for (unsigned int i = 0; i < count; i++) {
      data_size += ::_pbi::WireFormatLite::EnumSize(
        this->_internal_repeated_e(static_cast<int>(i)));
    }
    total_size += (1UL * count) + data_size;
  }

  // repeated .proto2_preserve_unknown_enum_unittest.MyEnum repeated_packed_e = 3 [packed = true];
  {
    size_t data_size = 0;
    unsigned int count = static_cast<unsigned int>(this->_internal_repeated_packed_e_size());for (unsigned int i = 0; i < count; i++) {
      data_size += ::_pbi::WireFormatLite::EnumSize(
        this->_internal_repeated_packed_e(static_cast<int>(i)));
    }
    if (data_size > 0) {
      total_size += 1 +
        ::_pbi::WireFormatLite::Int32Size(static_cast<int32_t>(data_size));
    }
    int cached_size = ::_pbi::ToCachedSize(data_size);
    _impl_._repeated_packed_e_cached_byte_size_.Set(cached_size);
    total_size += data_size;
  }

  // repeated .proto2_preserve_unknown_enum_unittest.MyEnum repeated_packed_unexpected_e = 4;
  {
    size_t data_size = 0;
    unsigned int count = static_cast<unsigned int>(this->_internal_repeated_packed_unexpected_e_size());for (unsigned int i = 0; i < count; i++) {
      data_size += ::_pbi::WireFormatLite::EnumSize(
        this->_internal_repeated_packed_unexpected_e(static_cast<int>(i)));
    }
    total_size += (1UL * count) + data_size;
  }

  // optional .proto2_preserve_unknown_enum_unittest.MyEnum e = 1;
  cached_has_bits = _impl_._has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    total_size += 1 +
      ::_pbi::WireFormatLite::EnumSize(this->_internal_e());
  }

  switch (o_case()) {
    // .proto2_preserve_unknown_enum_unittest.MyEnum oneof_e_1 = 5;
    case kOneofE1: {
      total_size += 1 +
        ::_pbi::WireFormatLite::EnumSize(this->_internal_oneof_e_1());
      break;
    }
    // .proto2_preserve_unknown_enum_unittest.MyEnum oneof_e_2 = 6;
    case kOneofE2: {
      total_size += 1 +
        ::_pbi::WireFormatLite::EnumSize(this->_internal_oneof_e_2());
      break;
    }
    case O_NOT_SET: {
      break;
    }
  }
  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData MyMessage::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    MyMessage::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*MyMessage::GetClassData() const { return &_class_data_; }


void MyMessage::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<MyMessage*>(&to_msg);
  auto& from = static_cast<const MyMessage&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:proto2_preserve_unknown_enum_unittest.MyMessage)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  _this->_impl_.repeated_e_.MergeFrom(from._impl_.repeated_e_);
  _this->_impl_.repeated_packed_e_.MergeFrom(from._impl_.repeated_packed_e_);
  _this->_impl_.repeated_packed_unexpected_e_.MergeFrom(from._impl_.repeated_packed_unexpected_e_);
  if (from._internal_has_e()) {
    _this->_internal_set_e(from._internal_e());
  }
  switch (from.o_case()) {
    case kOneofE1: {
      _this->_internal_set_oneof_e_1(from._internal_oneof_e_1());
      break;
    }
    case kOneofE2: {
      _this->_internal_set_oneof_e_2(from._internal_oneof_e_2());
      break;
    }
    case O_NOT_SET: {
      break;
    }
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void MyMessage::CopyFrom(const MyMessage& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:proto2_preserve_unknown_enum_unittest.MyMessage)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool MyMessage::IsInitialized() const {
  return true;
}

void MyMessage::InternalSwap(MyMessage* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_impl_._has_bits_[0], other->_impl_._has_bits_[0]);
  _impl_.repeated_e_.InternalSwap(&other->_impl_.repeated_e_);
  _impl_.repeated_packed_e_.InternalSwap(&other->_impl_.repeated_packed_e_);
  _impl_.repeated_packed_unexpected_e_.InternalSwap(&other->_impl_.repeated_packed_unexpected_e_);
  swap(_impl_.e_, other->_impl_.e_);
  swap(_impl_.o_, other->_impl_.o_);
  swap(_impl_._oneof_case_[0], other->_impl_._oneof_case_[0]);
}

::PROTOBUF_NAMESPACE_ID::Metadata MyMessage::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_google_2fprotobuf_2funittest_5fpreserve_5funknown_5fenum2_2eproto_getter, &descriptor_table_google_2fprotobuf_2funittest_5fpreserve_5funknown_5fenum2_2eproto_once,
      file_level_metadata_google_2fprotobuf_2funittest_5fpreserve_5funknown_5fenum2_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace proto2_preserve_unknown_enum_unittest
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::proto2_preserve_unknown_enum_unittest::MyMessage*
Arena::CreateMaybeMessage< ::proto2_preserve_unknown_enum_unittest::MyMessage >(Arena* arena) {
  return Arena::CreateMessageInternal< ::proto2_preserve_unknown_enum_unittest::MyMessage >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>