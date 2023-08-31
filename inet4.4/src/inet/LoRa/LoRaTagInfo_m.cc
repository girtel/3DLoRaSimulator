//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/LoRa/LoRaTagInfo.msg.
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
#include "LoRaTagInfo_m.h"

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

Register_Class(LoRaTag)

LoRaTag::LoRaTag() : ::inet::TagBase()
{
}

LoRaTag::LoRaTag(const LoRaTag& other) : ::inet::TagBase(other)
{
    copy(other);
}

LoRaTag::~LoRaTag()
{
}

LoRaTag& LoRaTag::operator=(const LoRaTag& other)
{
    if (this == &other) return *this;
    ::inet::TagBase::operator=(other);
    copy(other);
    return *this;
}

void LoRaTag::copy(const LoRaTag& other)
{
    this->centerFrequency = other.centerFrequency;
    this->bandwidth = other.bandwidth;
    this->spreadFactor = other.spreadFactor;
    this->power = other.power;
    this->UseHeader = other.UseHeader;
    this->codeRendundance = other.codeRendundance;
}

void LoRaTag::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::TagBase::parsimPack(b);
    doParsimPacking(b,this->centerFrequency);
    doParsimPacking(b,this->bandwidth);
    doParsimPacking(b,this->spreadFactor);
    doParsimPacking(b,this->power);
    doParsimPacking(b,this->UseHeader);
    doParsimPacking(b,this->codeRendundance);
}

void LoRaTag::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::TagBase::parsimUnpack(b);
    doParsimUnpacking(b,this->centerFrequency);
    doParsimUnpacking(b,this->bandwidth);
    doParsimUnpacking(b,this->spreadFactor);
    doParsimUnpacking(b,this->power);
    doParsimUnpacking(b,this->UseHeader);
    doParsimUnpacking(b,this->codeRendundance);
}

Hz LoRaTag::getCenterFrequency() const
{
    return this->centerFrequency;
}

void LoRaTag::setCenterFrequency(Hz centerFrequency)
{
    this->centerFrequency = centerFrequency;
}

Hz LoRaTag::getBandwidth() const
{
    return this->bandwidth;
}

void LoRaTag::setBandwidth(Hz bandwidth)
{
    this->bandwidth = bandwidth;
}

int LoRaTag::getSpreadFactor() const
{
    return this->spreadFactor;
}

void LoRaTag::setSpreadFactor(int spreadFactor)
{
    this->spreadFactor = spreadFactor;
}

W LoRaTag::getPower() const
{
    return this->power;
}

void LoRaTag::setPower(W power)
{
    this->power = power;
}

bool LoRaTag::getUseHeader() const
{
    return this->UseHeader;
}

void LoRaTag::setUseHeader(bool UseHeader)
{
    this->UseHeader = UseHeader;
}

int LoRaTag::getCodeRendundance() const
{
    return this->codeRendundance;
}

void LoRaTag::setCodeRendundance(int codeRendundance)
{
    this->codeRendundance = codeRendundance;
}

class LoRaTagDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_centerFrequency,
        FIELD_bandwidth,
        FIELD_spreadFactor,
        FIELD_power,
        FIELD_UseHeader,
        FIELD_codeRendundance,
    };
  public:
    LoRaTagDescriptor();
    virtual ~LoRaTagDescriptor();

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

Register_ClassDescriptor(LoRaTagDescriptor)

LoRaTagDescriptor::LoRaTagDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::LoRaTag)), "inet::TagBase")
{
    propertyNames = nullptr;
}

LoRaTagDescriptor::~LoRaTagDescriptor()
{
    delete[] propertyNames;
}

bool LoRaTagDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<LoRaTag *>(obj)!=nullptr;
}

const char **LoRaTagDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *LoRaTagDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int LoRaTagDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 6+base->getFieldCount() : 6;
}

unsigned int LoRaTagDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_centerFrequency
        FD_ISEDITABLE,    // FIELD_bandwidth
        FD_ISEDITABLE,    // FIELD_spreadFactor
        FD_ISEDITABLE,    // FIELD_power
        FD_ISEDITABLE,    // FIELD_UseHeader
        FD_ISEDITABLE,    // FIELD_codeRendundance
    };
    return (field >= 0 && field < 6) ? fieldTypeFlags[field] : 0;
}

const char *LoRaTagDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "centerFrequency",
        "bandwidth",
        "spreadFactor",
        "power",
        "UseHeader",
        "codeRendundance",
    };
    return (field >= 0 && field < 6) ? fieldNames[field] : nullptr;
}

int LoRaTagDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "centerFrequency") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "bandwidth") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "spreadFactor") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "power") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "UseHeader") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "codeRendundance") == 0) return baseIndex + 5;
    return base ? base->findField(fieldName) : -1;
}

const char *LoRaTagDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::Hz",    // FIELD_centerFrequency
        "inet::Hz",    // FIELD_bandwidth
        "int",    // FIELD_spreadFactor
        "inet::W",    // FIELD_power
        "bool",    // FIELD_UseHeader
        "int",    // FIELD_codeRendundance
    };
    return (field >= 0 && field < 6) ? fieldTypeStrings[field] : nullptr;
}

const char **LoRaTagDescriptor::getFieldPropertyNames(int field) const
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

const char *LoRaTagDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int LoRaTagDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    LoRaTag *pp = omnetpp::fromAnyPtr<LoRaTag>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void LoRaTagDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    LoRaTag *pp = omnetpp::fromAnyPtr<LoRaTag>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'LoRaTag'", field);
    }
}

const char *LoRaTagDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    LoRaTag *pp = omnetpp::fromAnyPtr<LoRaTag>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string LoRaTagDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    LoRaTag *pp = omnetpp::fromAnyPtr<LoRaTag>(object); (void)pp;
    switch (field) {
        case FIELD_centerFrequency: return unit2string(pp->getCenterFrequency());
        case FIELD_bandwidth: return unit2string(pp->getBandwidth());
        case FIELD_spreadFactor: return long2string(pp->getSpreadFactor());
        case FIELD_power: return unit2string(pp->getPower());
        case FIELD_UseHeader: return bool2string(pp->getUseHeader());
        case FIELD_codeRendundance: return long2string(pp->getCodeRendundance());
        default: return "";
    }
}

void LoRaTagDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LoRaTag *pp = omnetpp::fromAnyPtr<LoRaTag>(object); (void)pp;
    switch (field) {
        case FIELD_centerFrequency: pp->setCenterFrequency(Hz(string2double(value))); break;
        case FIELD_bandwidth: pp->setBandwidth(Hz(string2double(value))); break;
        case FIELD_spreadFactor: pp->setSpreadFactor(string2long(value)); break;
        case FIELD_power: pp->setPower(W(string2double(value))); break;
        case FIELD_UseHeader: pp->setUseHeader(string2bool(value)); break;
        case FIELD_codeRendundance: pp->setCodeRendundance(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LoRaTag'", field);
    }
}

omnetpp::cValue LoRaTagDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    LoRaTag *pp = omnetpp::fromAnyPtr<LoRaTag>(object); (void)pp;
    switch (field) {
        case FIELD_centerFrequency: return cValue(pp->getCenterFrequency().get(),"Hz");
        case FIELD_bandwidth: return cValue(pp->getBandwidth().get(),"Hz");
        case FIELD_spreadFactor: return pp->getSpreadFactor();
        case FIELD_power: return cValue(pp->getPower().get(),"W");
        case FIELD_UseHeader: return pp->getUseHeader();
        case FIELD_codeRendundance: return pp->getCodeRendundance();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'LoRaTag' as cValue -- field index out of range?", field);
    }
}

void LoRaTagDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LoRaTag *pp = omnetpp::fromAnyPtr<LoRaTag>(object); (void)pp;
    switch (field) {
        case FIELD_centerFrequency: pp->setCenterFrequency(Hz(value.doubleValueInUnit("Hz"))); break;
        case FIELD_bandwidth: pp->setBandwidth(Hz(value.doubleValueInUnit("Hz"))); break;
        case FIELD_spreadFactor: pp->setSpreadFactor(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_power: pp->setPower(W(value.doubleValueInUnit("W"))); break;
        case FIELD_UseHeader: pp->setUseHeader(value.boolValue()); break;
        case FIELD_codeRendundance: pp->setCodeRendundance(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LoRaTag'", field);
    }
}

const char *LoRaTagDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr LoRaTagDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    LoRaTag *pp = omnetpp::fromAnyPtr<LoRaTag>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void LoRaTagDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    LoRaTag *pp = omnetpp::fromAnyPtr<LoRaTag>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LoRaTag'", field);
    }
}

}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

