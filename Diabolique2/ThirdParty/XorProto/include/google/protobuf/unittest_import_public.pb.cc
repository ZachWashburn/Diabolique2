// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: google/protobuf/unittest_import_public.proto

#include "google/protobuf/unittest_import_public.pb.h"

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

namespace protobuf_unittest_import {
PROTOBUF_CONSTEXPR PublicImportMessage::PublicImportMessage(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_._has_bits_)*/{}
  , /*decltype(_impl_._cached_size_)*/{}
  , /*decltype(_impl_.e_)*/0} {}
struct PublicImportMessageDefaultTypeInternal {
  PROTOBUF_CONSTEXPR PublicImportMessageDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~PublicImportMessageDefaultTypeInternal() {}
  union {
    PublicImportMessage _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 PublicImportMessageDefaultTypeInternal _PublicImportMessage_default_instance_;
}  // namespace protobuf_unittest_import
static ::_pb::Metadata file_level_metadata_google_2fprotobuf_2funittest_5fimport_5fpublic_2eproto[1];
static constexpr ::_pb::EnumDescriptor const** file_level_enum_descriptors_google_2fprotobuf_2funittest_5fimport_5fpublic_2eproto = nullptr;
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_google_2fprotobuf_2funittest_5fimport_5fpublic_2eproto = nullptr;

const uint32_t TableStruct_google_2fprotobuf_2funittest_5fimport_5fpublic_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  PROTOBUF_FIELD_OFFSET(::protobuf_unittest_import::PublicImportMessage, _impl_._has_bits_),
  PROTOBUF_FIELD_OFFSET(::protobuf_unittest_import::PublicImportMessage, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  ~0u,  // no _split_
  ~0u,  // no sizeof(Split)
  PROTOBUF_FIELD_OFFSET(::protobuf_unittest_import::PublicImportMessage, _impl_.e_),
  0,
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 9, -1, sizeof(::protobuf_unittest_import::PublicImportMessage)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::protobuf_unittest_import::_PublicImportMessage_default_instance_._instance,
};

const char descriptor_table_protodef_google_2fprotobuf_2funittest_5fimport_5fpublic_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n,google/protobuf/unittest_import_public"
  ".proto\022\030protobuf_unittest_import\" \n\023Publ"
  "icImportMessage\022\t\n\001e\030\001 \001(\005B\032\n\030com.google"
  ".protobuf.test"
  ;
static ::_pbi::once_flag descriptor_table_google_2fprotobuf_2funittest_5fimport_5fpublic_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_google_2fprotobuf_2funittest_5fimport_5fpublic_2eproto = {
    false, false, 134, descriptor_table_protodef_google_2fprotobuf_2funittest_5fimport_5fpublic_2eproto,
    "google/protobuf/unittest_import_public.proto",
    &descriptor_table_google_2fprotobuf_2funittest_5fimport_5fpublic_2eproto_once, nullptr, 0, 1,
    schemas, file_default_instances, TableStruct_google_2fprotobuf_2funittest_5fimport_5fpublic_2eproto::offsets,
    file_level_metadata_google_2fprotobuf_2funittest_5fimport_5fpublic_2eproto, file_level_enum_descriptors_google_2fprotobuf_2funittest_5fimport_5fpublic_2eproto,
    file_level_service_descriptors_google_2fprotobuf_2funittest_5fimport_5fpublic_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_google_2fprotobuf_2funittest_5fimport_5fpublic_2eproto_getter() {
  return &descriptor_table_google_2fprotobuf_2funittest_5fimport_5fpublic_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_google_2fprotobuf_2funittest_5fimport_5fpublic_2eproto(&descriptor_table_google_2fprotobuf_2funittest_5fimport_5fpublic_2eproto);
namespace protobuf_unittest_import {

// ===================================================================

class PublicImportMessage::_Internal {
 public:
  using HasBits = decltype(std::declval<PublicImportMessage>()._impl_._has_bits_);
  static constexpr int32_t kHasBitsOffset =
    8 * PROTOBUF_FIELD_OFFSET(PublicImportMessage, _impl_._has_bits_);
  static void set_has_e(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
};

PublicImportMessage::PublicImportMessage(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:protobuf_unittest_import.PublicImportMessage)
}
PublicImportMessage::PublicImportMessage(const PublicImportMessage& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  PublicImportMessage* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_._has_bits_){from._impl_._has_bits_}
    , /*decltype(_impl_._cached_size_)*/{}
    , decltype(_impl_.e_){}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _this->_impl_.e_ = from._impl_.e_;
  // @@protoc_insertion_point(copy_constructor:protobuf_unittest_import.PublicImportMessage)
}

inline void PublicImportMessage::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_._has_bits_){}
    , /*decltype(_impl_._cached_size_)*/{}
    , decltype(_impl_.e_){0}
  };
}

PublicImportMessage::~PublicImportMessage() {
  // @@protoc_insertion_point(destructor:protobuf_unittest_import.PublicImportMessage)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void PublicImportMessage::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void PublicImportMessage::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void PublicImportMessage::Clear() {
// @@protoc_insertion_point(message_clear_start:protobuf_unittest_import.PublicImportMessage)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.e_ = 0;
  _impl_._has_bits_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* PublicImportMessage::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // optional int32 e = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          _Internal::set_has_e(&has_bits);
          _impl_.e_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
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

uint8_t* PublicImportMessage::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:protobuf_unittest_import.PublicImportMessage)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _impl_._has_bits_[0];
  // optional int32 e = 1;
  if (cached_has_bits & 0x00000001u) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(1, this->_internal_e(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:protobuf_unittest_import.PublicImportMessage)
  return target;
}

size_t PublicImportMessage::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:protobuf_unittest_import.PublicImportMessage)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // optional int32 e = 1;
  cached_has_bits = _impl_._has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_e());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData PublicImportMessage::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    PublicImportMessage::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*PublicImportMessage::GetClassData() const { return &_class_data_; }


void PublicImportMessage::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<PublicImportMessage*>(&to_msg);
  auto& from = static_cast<const PublicImportMessage&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:protobuf_unittest_import.PublicImportMessage)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (from._internal_has_e()) {
    _this->_internal_set_e(from._internal_e());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void PublicImportMessage::CopyFrom(const PublicImportMessage& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:protobuf_unittest_import.PublicImportMessage)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool PublicImportMessage::IsInitialized() const {
  return true;
}

void PublicImportMessage::InternalSwap(PublicImportMessage* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_impl_._has_bits_[0], other->_impl_._has_bits_[0]);
  swap(_impl_.e_, other->_impl_.e_);
}

::PROTOBUF_NAMESPACE_ID::Metadata PublicImportMessage::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_google_2fprotobuf_2funittest_5fimport_5fpublic_2eproto_getter, &descriptor_table_google_2fprotobuf_2funittest_5fimport_5fpublic_2eproto_once,
      file_level_metadata_google_2fprotobuf_2funittest_5fimport_5fpublic_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace protobuf_unittest_import
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::protobuf_unittest_import::PublicImportMessage*
Arena::CreateMaybeMessage< ::protobuf_unittest_import::PublicImportMessage >(Arena* arena) {
  return Arena::CreateMessageInternal< ::protobuf_unittest_import::PublicImportMessage >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
