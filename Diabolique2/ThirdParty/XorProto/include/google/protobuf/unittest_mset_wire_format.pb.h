// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: google/protobuf/unittest_mset_wire_format.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_google_2fprotobuf_2funittest_5fmset_5fwire_5fformat_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_google_2fprotobuf_2funittest_5fmset_5fwire_5fformat_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3021000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3021002 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_google_2fprotobuf_2funittest_5fmset_5fwire_5fformat_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_google_2fprotobuf_2funittest_5fmset_5fwire_5fformat_2eproto {
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_google_2fprotobuf_2funittest_5fmset_5fwire_5fformat_2eproto;
namespace proto2_wireformat_unittest {
class TestMessageSet;
struct TestMessageSetDefaultTypeInternal;
extern TestMessageSetDefaultTypeInternal _TestMessageSet_default_instance_;
class TestMessageSetWireFormatContainer;
struct TestMessageSetWireFormatContainerDefaultTypeInternal;
extern TestMessageSetWireFormatContainerDefaultTypeInternal _TestMessageSetWireFormatContainer_default_instance_;
}  // namespace proto2_wireformat_unittest
PROTOBUF_NAMESPACE_OPEN
template<> ::proto2_wireformat_unittest::TestMessageSet* Arena::CreateMaybeMessage<::proto2_wireformat_unittest::TestMessageSet>(Arena*);
template<> ::proto2_wireformat_unittest::TestMessageSetWireFormatContainer* Arena::CreateMaybeMessage<::proto2_wireformat_unittest::TestMessageSetWireFormatContainer>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace proto2_wireformat_unittest {

// ===================================================================

class TestMessageSet final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:proto2_wireformat_unittest.TestMessageSet) */ {
 public:
  inline TestMessageSet() : TestMessageSet(nullptr) {}
  ~TestMessageSet() override;
  explicit PROTOBUF_CONSTEXPR TestMessageSet(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  TestMessageSet(const TestMessageSet& from);
  TestMessageSet(TestMessageSet&& from) noexcept
    : TestMessageSet() {
    *this = ::std::move(from);
  }

  inline TestMessageSet& operator=(const TestMessageSet& from) {
    CopyFrom(from);
    return *this;
  }
  inline TestMessageSet& operator=(TestMessageSet&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance);
  }
  inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const TestMessageSet& default_instance() {
    return *internal_default_instance();
  }
  static inline const TestMessageSet* internal_default_instance() {
    return reinterpret_cast<const TestMessageSet*>(
               &_TestMessageSet_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(TestMessageSet& a, TestMessageSet& b) {
    a.Swap(&b);
  }
  inline void Swap(TestMessageSet* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(TestMessageSet* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  TestMessageSet* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<TestMessageSet>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const TestMessageSet& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const TestMessageSet& from) {
    TestMessageSet::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(TestMessageSet* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "proto2_wireformat_unittest.TestMessageSet";
  }
  protected:
  explicit TestMessageSet(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------


  template <typename _proto_TypeTraits,
            ::PROTOBUF_NAMESPACE_ID::internal::FieldType _field_type,
            bool _is_packed>
  inline bool HasExtension(
      const ::PROTOBUF_NAMESPACE_ID::internal::ExtensionIdentifier<
          TestMessageSet, _proto_TypeTraits, _field_type, _is_packed>& id) const {

    return _impl_._extensions_.Has(id.number());
  }

  template <typename _proto_TypeTraits,
            ::PROTOBUF_NAMESPACE_ID::internal::FieldType _field_type,
            bool _is_packed>
  inline void ClearExtension(
      const ::PROTOBUF_NAMESPACE_ID::internal::ExtensionIdentifier<
          TestMessageSet, _proto_TypeTraits, _field_type, _is_packed>& id) {
    _impl_._extensions_.ClearExtension(id.number());

  }

  template <typename _proto_TypeTraits,
            ::PROTOBUF_NAMESPACE_ID::internal::FieldType _field_type,
            bool _is_packed>
  inline int ExtensionSize(
      const ::PROTOBUF_NAMESPACE_ID::internal::ExtensionIdentifier<
          TestMessageSet, _proto_TypeTraits, _field_type, _is_packed>& id) const {

    return _impl_._extensions_.ExtensionSize(id.number());
  }

  template <typename _proto_TypeTraits,
            ::PROTOBUF_NAMESPACE_ID::internal::FieldType _field_type,
            bool _is_packed>
  inline typename _proto_TypeTraits::Singular::ConstType GetExtension(
      const ::PROTOBUF_NAMESPACE_ID::internal::ExtensionIdentifier<
          TestMessageSet, _proto_TypeTraits, _field_type, _is_packed>& id) const {

    return _proto_TypeTraits::Get(id.number(), _impl_._extensions_,
                                  id.default_value());
  }

  template <typename _proto_TypeTraits,
            ::PROTOBUF_NAMESPACE_ID::internal::FieldType _field_type,
            bool _is_packed>
  inline typename _proto_TypeTraits::Singular::MutableType MutableExtension(
      const ::PROTOBUF_NAMESPACE_ID::internal::ExtensionIdentifier<
          TestMessageSet, _proto_TypeTraits, _field_type, _is_packed>& id) {

    return _proto_TypeTraits::Mutable(id.number(), _field_type,
                                      &_impl_._extensions_);
  }

  template <typename _proto_TypeTraits,
            ::PROTOBUF_NAMESPACE_ID::internal::FieldType _field_type,
            bool _is_packed>
  inline void SetExtension(
      const ::PROTOBUF_NAMESPACE_ID::internal::ExtensionIdentifier<
          TestMessageSet, _proto_TypeTraits, _field_type, _is_packed>& id,
      typename _proto_TypeTraits::Singular::ConstType value) {
    _proto_TypeTraits::Set(id.number(), _field_type, value, &_impl_._extensions_);

  }

  template <typename _proto_TypeTraits,
            ::PROTOBUF_NAMESPACE_ID::internal::FieldType _field_type,
            bool _is_packed>
  inline void SetAllocatedExtension(
      const ::PROTOBUF_NAMESPACE_ID::internal::ExtensionIdentifier<
          TestMessageSet, _proto_TypeTraits, _field_type, _is_packed>& id,
      typename _proto_TypeTraits::Singular::MutableType value) {
    _proto_TypeTraits::SetAllocated(id.number(), _field_type, value,
                                    &_impl_._extensions_);

  }
  template <typename _proto_TypeTraits,
            ::PROTOBUF_NAMESPACE_ID::internal::FieldType _field_type,
            bool _is_packed>
  inline void UnsafeArenaSetAllocatedExtension(
      const ::PROTOBUF_NAMESPACE_ID::internal::ExtensionIdentifier<
          TestMessageSet, _proto_TypeTraits, _field_type, _is_packed>& id,
      typename _proto_TypeTraits::Singular::MutableType value) {
    _proto_TypeTraits::UnsafeArenaSetAllocated(id.number(), _field_type,
                                               value, &_impl_._extensions_);

  }
  template <typename _proto_TypeTraits,
            ::PROTOBUF_NAMESPACE_ID::internal::FieldType _field_type,
            bool _is_packed>
  PROTOBUF_NODISCARD inline
      typename _proto_TypeTraits::Singular::MutableType
      ReleaseExtension(
          const ::PROTOBUF_NAMESPACE_ID::internal::ExtensionIdentifier<
              TestMessageSet, _proto_TypeTraits, _field_type, _is_packed>& id) {

    return _proto_TypeTraits::Release(id.number(), _field_type,
                                      &_impl_._extensions_);
  }
  template <typename _proto_TypeTraits,
            ::PROTOBUF_NAMESPACE_ID::internal::FieldType _field_type,
            bool _is_packed>
  inline typename _proto_TypeTraits::Singular::MutableType
  UnsafeArenaReleaseExtension(
      const ::PROTOBUF_NAMESPACE_ID::internal::ExtensionIdentifier<
          TestMessageSet, _proto_TypeTraits, _field_type, _is_packed>& id) {

    return _proto_TypeTraits::UnsafeArenaRelease(id.number(), _field_type,
                                                 &_impl_._extensions_);
  }

  template <typename _proto_TypeTraits,
            ::PROTOBUF_NAMESPACE_ID::internal::FieldType _field_type,
            bool _is_packed>
  inline typename _proto_TypeTraits::Repeated::ConstType GetExtension(
      const ::PROTOBUF_NAMESPACE_ID::internal::ExtensionIdentifier<
          TestMessageSet, _proto_TypeTraits, _field_type, _is_packed>& id,
      int index) const {

    return _proto_TypeTraits::Get(id.number(), _impl_._extensions_, index);
  }

  template <typename _proto_TypeTraits,
            ::PROTOBUF_NAMESPACE_ID::internal::FieldType _field_type,
            bool _is_packed>
  inline typename _proto_TypeTraits::Repeated::MutableType MutableExtension(
      const ::PROTOBUF_NAMESPACE_ID::internal::ExtensionIdentifier<
          TestMessageSet, _proto_TypeTraits, _field_type, _is_packed>& id,
      int index) {

    return _proto_TypeTraits::Mutable(id.number(), index, &_impl_._extensions_);
  }

  template <typename _proto_TypeTraits,
            ::PROTOBUF_NAMESPACE_ID::internal::FieldType _field_type,
            bool _is_packed>
  inline void SetExtension(
      const ::PROTOBUF_NAMESPACE_ID::internal::ExtensionIdentifier<
          TestMessageSet, _proto_TypeTraits, _field_type, _is_packed>& id,
      int index, typename _proto_TypeTraits::Repeated::ConstType value) {
    _proto_TypeTraits::Set(id.number(), index, value, &_impl_._extensions_);

  }

  template <typename _proto_TypeTraits,
            ::PROTOBUF_NAMESPACE_ID::internal::FieldType _field_type,
            bool _is_packed>
  inline typename _proto_TypeTraits::Repeated::MutableType AddExtension(
      const ::PROTOBUF_NAMESPACE_ID::internal::ExtensionIdentifier<
          TestMessageSet, _proto_TypeTraits, _field_type, _is_packed>& id) {
    typename _proto_TypeTraits::Repeated::MutableType to_add =
        _proto_TypeTraits::Add(id.number(), _field_type, &_impl_._extensions_);

    return to_add;
  }

  template <typename _proto_TypeTraits,
            ::PROTOBUF_NAMESPACE_ID::internal::FieldType _field_type,
            bool _is_packed>
  inline void AddExtension(
      const ::PROTOBUF_NAMESPACE_ID::internal::ExtensionIdentifier<
          TestMessageSet, _proto_TypeTraits, _field_type, _is_packed>& id,
      typename _proto_TypeTraits::Repeated::ConstType value) {
    _proto_TypeTraits::Add(id.number(), _field_type, _is_packed, value,
                           &_impl_._extensions_);

  }

  template <typename _proto_TypeTraits,
            ::PROTOBUF_NAMESPACE_ID::internal::FieldType _field_type,
            bool _is_packed>
  inline const typename _proto_TypeTraits::Repeated::RepeatedFieldType&
  GetRepeatedExtension(
      const ::PROTOBUF_NAMESPACE_ID::internal::ExtensionIdentifier<
          TestMessageSet, _proto_TypeTraits, _field_type, _is_packed>& id) const {

    return _proto_TypeTraits::GetRepeated(id.number(), _impl_._extensions_);
  }

  template <typename _proto_TypeTraits,
            ::PROTOBUF_NAMESPACE_ID::internal::FieldType _field_type,
            bool _is_packed>
  inline typename _proto_TypeTraits::Repeated::RepeatedFieldType*
  MutableRepeatedExtension(
      const ::PROTOBUF_NAMESPACE_ID::internal::ExtensionIdentifier<
          TestMessageSet, _proto_TypeTraits, _field_type, _is_packed>& id) {

    return _proto_TypeTraits::MutableRepeated(id.number(), _field_type,
                                              _is_packed, &_impl_._extensions_);
  }

  // @@protoc_insertion_point(class_scope:proto2_wireformat_unittest.TestMessageSet)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::internal::ExtensionSet _extensions_;

    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_google_2fprotobuf_2funittest_5fmset_5fwire_5fformat_2eproto;
};
// -------------------------------------------------------------------

class TestMessageSetWireFormatContainer final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:proto2_wireformat_unittest.TestMessageSetWireFormatContainer) */ {
 public:
  inline TestMessageSetWireFormatContainer() : TestMessageSetWireFormatContainer(nullptr) {}
  ~TestMessageSetWireFormatContainer() override;
  explicit PROTOBUF_CONSTEXPR TestMessageSetWireFormatContainer(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  TestMessageSetWireFormatContainer(const TestMessageSetWireFormatContainer& from);
  TestMessageSetWireFormatContainer(TestMessageSetWireFormatContainer&& from) noexcept
    : TestMessageSetWireFormatContainer() {
    *this = ::std::move(from);
  }

  inline TestMessageSetWireFormatContainer& operator=(const TestMessageSetWireFormatContainer& from) {
    CopyFrom(from);
    return *this;
  }
  inline TestMessageSetWireFormatContainer& operator=(TestMessageSetWireFormatContainer&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance);
  }
  inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const TestMessageSetWireFormatContainer& default_instance() {
    return *internal_default_instance();
  }
  static inline const TestMessageSetWireFormatContainer* internal_default_instance() {
    return reinterpret_cast<const TestMessageSetWireFormatContainer*>(
               &_TestMessageSetWireFormatContainer_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(TestMessageSetWireFormatContainer& a, TestMessageSetWireFormatContainer& b) {
    a.Swap(&b);
  }
  inline void Swap(TestMessageSetWireFormatContainer* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(TestMessageSetWireFormatContainer* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  TestMessageSetWireFormatContainer* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<TestMessageSetWireFormatContainer>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const TestMessageSetWireFormatContainer& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const TestMessageSetWireFormatContainer& from) {
    TestMessageSetWireFormatContainer::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(TestMessageSetWireFormatContainer* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "proto2_wireformat_unittest.TestMessageSetWireFormatContainer";
  }
  protected:
  explicit TestMessageSetWireFormatContainer(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kMessageSetFieldNumber = 1,
  };
  // optional .proto2_wireformat_unittest.TestMessageSet message_set = 1;
  bool has_message_set() const;
  private:
  bool _internal_has_message_set() const;
  public:
  void clear_message_set();
  const ::proto2_wireformat_unittest::TestMessageSet& message_set() const;
  PROTOBUF_NODISCARD ::proto2_wireformat_unittest::TestMessageSet* release_message_set();
  ::proto2_wireformat_unittest::TestMessageSet* mutable_message_set();
  void set_allocated_message_set(::proto2_wireformat_unittest::TestMessageSet* message_set);
  private:
  const ::proto2_wireformat_unittest::TestMessageSet& _internal_message_set() const;
  ::proto2_wireformat_unittest::TestMessageSet* _internal_mutable_message_set();
  public:
  void unsafe_arena_set_allocated_message_set(
      ::proto2_wireformat_unittest::TestMessageSet* message_set);
  ::proto2_wireformat_unittest::TestMessageSet* unsafe_arena_release_message_set();

  // @@protoc_insertion_point(class_scope:proto2_wireformat_unittest.TestMessageSetWireFormatContainer)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
    ::proto2_wireformat_unittest::TestMessageSet* message_set_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_google_2fprotobuf_2funittest_5fmset_5fwire_5fformat_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// TestMessageSet

// -------------------------------------------------------------------

// TestMessageSetWireFormatContainer

// optional .proto2_wireformat_unittest.TestMessageSet message_set = 1;
inline bool TestMessageSetWireFormatContainer::_internal_has_message_set() const {
  bool value = (_impl_._has_bits_[0] & 0x00000001u) != 0;
  PROTOBUF_ASSUME(!value || _impl_.message_set_ != nullptr);
  return value;
}
inline bool TestMessageSetWireFormatContainer::has_message_set() const {
  return _internal_has_message_set();
}
inline void TestMessageSetWireFormatContainer::clear_message_set() {
  if (_impl_.message_set_ != nullptr) _impl_.message_set_->Clear();
  _impl_._has_bits_[0] &= ~0x00000001u;
}
inline const ::proto2_wireformat_unittest::TestMessageSet& TestMessageSetWireFormatContainer::_internal_message_set() const {
  const ::proto2_wireformat_unittest::TestMessageSet* p = _impl_.message_set_;
  return p != nullptr ? *p : reinterpret_cast<const ::proto2_wireformat_unittest::TestMessageSet&>(
      ::proto2_wireformat_unittest::_TestMessageSet_default_instance_);
}
inline const ::proto2_wireformat_unittest::TestMessageSet& TestMessageSetWireFormatContainer::message_set() const {
  // @@protoc_insertion_point(field_get:proto2_wireformat_unittest.TestMessageSetWireFormatContainer.message_set)
  return _internal_message_set();
}
inline void TestMessageSetWireFormatContainer::unsafe_arena_set_allocated_message_set(
    ::proto2_wireformat_unittest::TestMessageSet* message_set) {
  if (GetArenaForAllocation() == nullptr) {
    delete reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(_impl_.message_set_);
  }
  _impl_.message_set_ = message_set;
  if (message_set) {
    _impl_._has_bits_[0] |= 0x00000001u;
  } else {
    _impl_._has_bits_[0] &= ~0x00000001u;
  }
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:proto2_wireformat_unittest.TestMessageSetWireFormatContainer.message_set)
}
inline ::proto2_wireformat_unittest::TestMessageSet* TestMessageSetWireFormatContainer::release_message_set() {
  _impl_._has_bits_[0] &= ~0x00000001u;
  ::proto2_wireformat_unittest::TestMessageSet* temp = _impl_.message_set_;
  _impl_.message_set_ = nullptr;
#ifdef PROTOBUF_FORCE_COPY_IN_RELEASE
  auto* old =  reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(temp);
  temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  if (GetArenaForAllocation() == nullptr) { delete old; }
#else  // PROTOBUF_FORCE_COPY_IN_RELEASE
  if (GetArenaForAllocation() != nullptr) {
    temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  }
#endif  // !PROTOBUF_FORCE_COPY_IN_RELEASE
  return temp;
}
inline ::proto2_wireformat_unittest::TestMessageSet* TestMessageSetWireFormatContainer::unsafe_arena_release_message_set() {
  // @@protoc_insertion_point(field_release:proto2_wireformat_unittest.TestMessageSetWireFormatContainer.message_set)
  _impl_._has_bits_[0] &= ~0x00000001u;
  ::proto2_wireformat_unittest::TestMessageSet* temp = _impl_.message_set_;
  _impl_.message_set_ = nullptr;
  return temp;
}
inline ::proto2_wireformat_unittest::TestMessageSet* TestMessageSetWireFormatContainer::_internal_mutable_message_set() {
  _impl_._has_bits_[0] |= 0x00000001u;
  if (_impl_.message_set_ == nullptr) {
    auto* p = CreateMaybeMessage<::proto2_wireformat_unittest::TestMessageSet>(GetArenaForAllocation());
    _impl_.message_set_ = p;
  }
  return _impl_.message_set_;
}
inline ::proto2_wireformat_unittest::TestMessageSet* TestMessageSetWireFormatContainer::mutable_message_set() {
  ::proto2_wireformat_unittest::TestMessageSet* _msg = _internal_mutable_message_set();
  // @@protoc_insertion_point(field_mutable:proto2_wireformat_unittest.TestMessageSetWireFormatContainer.message_set)
  return _msg;
}
inline void TestMessageSetWireFormatContainer::set_allocated_message_set(::proto2_wireformat_unittest::TestMessageSet* message_set) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaForAllocation();
  if (message_arena == nullptr) {
    delete _impl_.message_set_;
  }
  if (message_set) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena =
        ::PROTOBUF_NAMESPACE_ID::Arena::InternalGetOwningArena(message_set);
    if (message_arena != submessage_arena) {
      message_set = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, message_set, submessage_arena);
    }
    _impl_._has_bits_[0] |= 0x00000001u;
  } else {
    _impl_._has_bits_[0] &= ~0x00000001u;
  }
  _impl_.message_set_ = message_set;
  // @@protoc_insertion_point(field_set_allocated:proto2_wireformat_unittest.TestMessageSetWireFormatContainer.message_set)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace proto2_wireformat_unittest

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_google_2fprotobuf_2funittest_5fmset_5fwire_5fformat_2eproto
