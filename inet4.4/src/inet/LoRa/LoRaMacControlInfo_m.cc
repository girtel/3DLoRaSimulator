//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/LoRa/LoRaMacControlInfo.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "LoRaMacControlInfo_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

namespace inet {

LoRaMacControlInfo::LoRaMacControlInfo()
{
}

LoRaMacControlInfo::LoRaMacControlInfo(const LoRaMacControlInfo& other)
{
    copy(other);
}

LoRaMacControlInfo::~LoRaMacControlInfo()
{
}

LoRaMacControlInfo& LoRaMacControlInfo::operator=(const LoRaMacControlInfo& other)
{
    if (this == &other) return *this;
    copy(other);
    return *this;
}

void LoRaMacControlInfo::copy(const LoRaMacControlInfo& other)
{
    this->src = other.src;
    this->dest = other.dest;
    this->LoRaTP = other.LoRaTP;
    this->LoRaCF = other.LoRaCF;
    this->LoRaSF = other.LoRaSF;
    this->LoRaBW = other.LoRaBW;
    this->LoRaCR = other.LoRaCR;
    this->LoRaUseHeader = other.LoRaUseHeader;
}

void LoRaMacControlInfo::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->src);
    doParsimPacking(b,this->dest);
    doParsimPacking(b,this->LoRaTP);
    doParsimPacking(b,this->LoRaCF);
    doParsimPacking(b,this->LoRaSF);
    doParsimPacking(b,this->LoRaBW);
    doParsimPacking(b,this->LoRaCR);
    doParsimPacking(b,this->LoRaUseHeader);
}

void LoRaMacControlInfo::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->src);
    doParsimUnpacking(b,this->dest);
    doParsimUnpacking(b,this->LoRaTP);
    doParsimUnpacking(b,this->LoRaCF);
    doParsimUnpacking(b,this->LoRaSF);
    doParsimUnpacking(b,this->LoRaBW);
    doParsimUnpacking(b,this->LoRaCR);
    doParsimUnpacking(b,this->LoRaUseHeader);
}

const MacAddress& LoRaMacControlInfo::getSrc() const
{
    return this->src;
}

void LoRaMacControlInfo::setSrc(const MacAddress& src)
{
    this->src = src;
}

const MacAddress& LoRaMacControlInfo::getDest() const
{
    return this->dest;
}

void LoRaMacControlInfo::setDest(const MacAddress& dest)
{
    this->dest = dest;
}

double LoRaMacControlInfo::getLoRaTP() const
{
    return this->LoRaTP;
}

void LoRaMacControlInfo::setLoRaTP(double LoRaTP)
{
    this->LoRaTP = LoRaTP;
}

Hz LoRaMacControlInfo::getLoRaCF() const
{
    return this->LoRaCF;
}

void LoRaMacControlInfo::setLoRaCF(Hz LoRaCF)
{
    this->LoRaCF = LoRaCF;
}

int LoRaMacControlInfo::getLoRaSF() const
{
    return this->LoRaSF;
}

void LoRaMacControlInfo::setLoRaSF(int LoRaSF)
{
    this->LoRaSF = LoRaSF;
}

Hz LoRaMacControlInfo::getLoRaBW() const
{
    return this->LoRaBW;
}

void LoRaMacControlInfo::setLoRaBW(Hz LoRaBW)
{
    this->LoRaBW = LoRaBW;
}

int LoRaMacControlInfo::getLoRaCR() const
{
    return this->LoRaCR;
}

void LoRaMacControlInfo::setLoRaCR(int LoRaCR)
{
    this->LoRaCR = LoRaCR;
}

bool LoRaMacControlInfo::getLoRaUseHeader() const
{
    return this->LoRaUseHeader;
}

void LoRaMacControlInfo::setLoRaUseHeader(bool LoRaUseHeader)
{
    this->LoRaUseHeader = LoRaUseHeader;
}

class LoRaMacControlInfoDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_src,
        FIELD_dest,
        FIELD_LoRaTP,
        FIELD_LoRaCF,
        FIELD_LoRaSF,
        FIELD_LoRaBW,
        FIELD_LoRaCR,
        FIELD_LoRaUseHeader,
    };
  public:
    LoRaMacControlInfoDescriptor();
    virtual ~LoRaMacControlInfoDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(LoRaMacControlInfoDescriptor)

LoRaMacControlInfoDescriptor::LoRaMacControlInfoDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::LoRaMacControlInfo)), "")
{
    propertyNames = nullptr;
}

LoRaMacControlInfoDescriptor::~LoRaMacControlInfoDescriptor()
{
    delete[] propertyNames;
}

bool LoRaMacControlInfoDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<LoRaMacControlInfo *>(obj)!=nullptr;
}

const char **LoRaMacControlInfoDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *LoRaMacControlInfoDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int LoRaMacControlInfoDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 8+base->getFieldCount() : 8;
}

unsigned int LoRaMacControlInfoDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_src
        0,    // FIELD_dest
        FD_ISEDITABLE,    // FIELD_LoRaTP
        FD_ISEDITABLE,    // FIELD_LoRaCF
        FD_ISEDITABLE,    // FIELD_LoRaSF
        FD_ISEDITABLE,    // FIELD_LoRaBW
        FD_ISEDITABLE,    // FIELD_LoRaCR
        FD_ISEDITABLE,    // FIELD_LoRaUseHeader
    };
    return (field >= 0 && field < 8) ? fieldTypeFlags[field] : 0;
}

const char *LoRaMacControlInfoDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "src",
        "dest",
        "LoRaTP",
        "LoRaCF",
        "LoRaSF",
        "LoRaBW",
        "LoRaCR",
        "LoRaUseHeader",
    };
    return (field >= 0 && field < 8) ? fieldNames[field] : nullptr;
}

int LoRaMacControlInfoDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "src") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "dest") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "LoRaTP") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "LoRaCF") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "LoRaSF") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "LoRaBW") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "LoRaCR") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "LoRaUseHeader") == 0) return baseIndex + 7;
    return base ? base->findField(fieldName) : -1;
}

const char *LoRaMacControlInfoDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::MacAddress",    // FIELD_src
        "inet::MacAddress",    // FIELD_dest
        "double",    // FIELD_LoRaTP
        "inet::Hz",    // FIELD_LoRaCF
        "int",    // FIELD_LoRaSF
        "inet::Hz",    // FIELD_LoRaBW
        "int",    // FIELD_LoRaCR
        "bool",    // FIELD_LoRaUseHeader
    };
    return (field >= 0 && field < 8) ? fieldTypeStrings[field] : nullptr;
}

const char **LoRaMacControlInfoDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *LoRaMacControlInfoDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int LoRaMacControlInfoDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    LoRaMacControlInfo *pp = omnetpp::fromAnyPtr<LoRaMacControlInfo>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void LoRaMacControlInfoDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    LoRaMacControlInfo *pp = omnetpp::fromAnyPtr<LoRaMacControlInfo>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'LoRaMacControlInfo'", field);
    }
}

const char *LoRaMacControlInfoDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    LoRaMacControlInfo *pp = omnetpp::fromAnyPtr<LoRaMacControlInfo>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string LoRaMacControlInfoDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    LoRaMacControlInfo *pp = omnetpp::fromAnyPtr<LoRaMacControlInfo>(object); (void)pp;
    switch (field) {
        case FIELD_src: return pp->getSrc().str();
        case FIELD_dest: return pp->getDest().str();
        case FIELD_LoRaTP: return double2string(pp->getLoRaTP());
        case FIELD_LoRaCF: return unit2string(pp->getLoRaCF());
        case FIELD_LoRaSF: return long2string(pp->getLoRaSF());
        case FIELD_LoRaBW: return unit2string(pp->getLoRaBW());
        case FIELD_LoRaCR: return long2string(pp->getLoRaCR());
        case FIELD_LoRaUseHeader: return bool2string(pp->getLoRaUseHeader());
        default: return "";
    }
}

void LoRaMacControlInfoDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LoRaMacControlInfo *pp = omnetpp::fromAnyPtr<LoRaMacControlInfo>(object); (void)pp;
    switch (field) {
        case FIELD_LoRaTP: pp->setLoRaTP(string2double(value)); break;
        case FIELD_LoRaCF: pp->setLoRaCF(Hz(string2double(value))); break;
        case FIELD_LoRaSF: pp->setLoRaSF(string2long(value)); break;
        case FIELD_LoRaBW: pp->setLoRaBW(Hz(string2double(value))); break;
        case FIELD_LoRaCR: pp->setLoRaCR(string2long(value)); break;
        case FIELD_LoRaUseHeader: pp->setLoRaUseHeader(string2bool(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LoRaMacControlInfo'", field);
    }
}

omnetpp::cValue LoRaMacControlInfoDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    LoRaMacControlInfo *pp = omnetpp::fromAnyPtr<LoRaMacControlInfo>(object); (void)pp;
    switch (field) {
        case FIELD_src: return omnetpp::toAnyPtr(&pp->getSrc()); break;
        case FIELD_dest: return omnetpp::toAnyPtr(&pp->getDest()); break;
        case FIELD_LoRaTP: return pp->getLoRaTP();
        case FIELD_LoRaCF: return cValue(pp->getLoRaCF().get(),"Hz");
        case FIELD_LoRaSF: return pp->getLoRaSF();
        case FIELD_LoRaBW: return cValue(pp->getLoRaBW().get(),"Hz");
        case FIELD_LoRaCR: return pp->getLoRaCR();
        case FIELD_LoRaUseHeader: return pp->getLoRaUseHeader();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'LoRaMacControlInfo' as cValue -- field index out of range?", field);
    }
}

void LoRaMacControlInfoDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LoRaMacControlInfo *pp = omnetpp::fromAnyPtr<LoRaMacControlInfo>(object); (void)pp;
    switch (field) {
        case FIELD_LoRaTP: pp->setLoRaTP(value.doubleValue()); break;
        case FIELD_LoRaCF: pp->setLoRaCF(Hz(value.doubleValueInUnit("Hz"))); break;
        case FIELD_LoRaSF: pp->setLoRaSF(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_LoRaBW: pp->setLoRaBW(Hz(value.doubleValueInUnit("Hz"))); break;
        case FIELD_LoRaCR: pp->setLoRaCR(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_LoRaUseHeader: pp->setLoRaUseHeader(value.boolValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LoRaMacControlInfo'", field);
    }
}

const char *LoRaMacControlInfoDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr LoRaMacControlInfoDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    LoRaMacControlInfo *pp = omnetpp::fromAnyPtr<LoRaMacControlInfo>(object); (void)pp;
    switch (field) {
        case FIELD_src: return omnetpp::toAnyPtr(&pp->getSrc()); break;
        case FIELD_dest: return omnetpp::toAnyPtr(&pp->getDest()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void LoRaMacControlInfoDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    LoRaMacControlInfo *pp = omnetpp::fromAnyPtr<LoRaMacControlInfo>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LoRaMacControlInfo'", field);
    }
}

}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

