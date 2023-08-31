//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/LoRaApp/LoRaAppPacket.msg.
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
#include "LoRaAppPacket_m.h"

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

Register_Enum(inet::AppPacketType, (inet::AppPacketType::JOIN_REQUEST, inet::AppPacketType::JOIN_REPLY, inet::AppPacketType::DATA, inet::AppPacketType::TXCONFIG));

LoRaOptions::LoRaOptions()
{
}

LoRaOptions::LoRaOptions(const LoRaOptions& other)
{
    copy(other);
}

LoRaOptions::~LoRaOptions()
{
}

LoRaOptions& LoRaOptions::operator=(const LoRaOptions& other)
{
    if (this == &other) return *this;
    copy(other);
    return *this;
}

void LoRaOptions::copy(const LoRaOptions& other)
{
    this->LoRaTP = other.LoRaTP;
    this->LoRaCF = other.LoRaCF;
    this->LoRaSF = other.LoRaSF;
    this->LoRaBW = other.LoRaBW;
    this->LoRaCR = other.LoRaCR;
    this->UseHeader = other.UseHeader;
    this->ADRACKReq = other.ADRACKReq;
}

void LoRaOptions::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->LoRaTP);
    doParsimPacking(b,this->LoRaCF);
    doParsimPacking(b,this->LoRaSF);
    doParsimPacking(b,this->LoRaBW);
    doParsimPacking(b,this->LoRaCR);
    doParsimPacking(b,this->UseHeader);
    doParsimPacking(b,this->ADRACKReq);
}

void LoRaOptions::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->LoRaTP);
    doParsimUnpacking(b,this->LoRaCF);
    doParsimUnpacking(b,this->LoRaSF);
    doParsimUnpacking(b,this->LoRaBW);
    doParsimUnpacking(b,this->LoRaCR);
    doParsimUnpacking(b,this->UseHeader);
    doParsimUnpacking(b,this->ADRACKReq);
}

double LoRaOptions::getLoRaTP() const
{
    return this->LoRaTP;
}

void LoRaOptions::setLoRaTP(double LoRaTP)
{
    this->LoRaTP = LoRaTP;
}

double LoRaOptions::getLoRaCF() const
{
    return this->LoRaCF;
}

void LoRaOptions::setLoRaCF(double LoRaCF)
{
    this->LoRaCF = LoRaCF;
}

int LoRaOptions::getLoRaSF() const
{
    return this->LoRaSF;
}

void LoRaOptions::setLoRaSF(int LoRaSF)
{
    this->LoRaSF = LoRaSF;
}

double LoRaOptions::getLoRaBW() const
{
    return this->LoRaBW;
}

void LoRaOptions::setLoRaBW(double LoRaBW)
{
    this->LoRaBW = LoRaBW;
}

int LoRaOptions::getLoRaCR() const
{
    return this->LoRaCR;
}

void LoRaOptions::setLoRaCR(int LoRaCR)
{
    this->LoRaCR = LoRaCR;
}

bool LoRaOptions::getUseHeader() const
{
    return this->UseHeader;
}

void LoRaOptions::setUseHeader(bool UseHeader)
{
    this->UseHeader = UseHeader;
}

bool LoRaOptions::getADRACKReq() const
{
    return this->ADRACKReq;
}

void LoRaOptions::setADRACKReq(bool ADRACKReq)
{
    this->ADRACKReq = ADRACKReq;
}

class LoRaOptionsDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_LoRaTP,
        FIELD_LoRaCF,
        FIELD_LoRaSF,
        FIELD_LoRaBW,
        FIELD_LoRaCR,
        FIELD_UseHeader,
        FIELD_ADRACKReq,
    };
  public:
    LoRaOptionsDescriptor();
    virtual ~LoRaOptionsDescriptor();

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

Register_ClassDescriptor(LoRaOptionsDescriptor)

LoRaOptionsDescriptor::LoRaOptionsDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::LoRaOptions)), "")
{
    propertyNames = nullptr;
}

LoRaOptionsDescriptor::~LoRaOptionsDescriptor()
{
    delete[] propertyNames;
}

bool LoRaOptionsDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<LoRaOptions *>(obj)!=nullptr;
}

const char **LoRaOptionsDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *LoRaOptionsDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int LoRaOptionsDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 7+base->getFieldCount() : 7;
}

unsigned int LoRaOptionsDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_LoRaTP
        FD_ISEDITABLE,    // FIELD_LoRaCF
        FD_ISEDITABLE,    // FIELD_LoRaSF
        FD_ISEDITABLE,    // FIELD_LoRaBW
        FD_ISEDITABLE,    // FIELD_LoRaCR
        FD_ISEDITABLE,    // FIELD_UseHeader
        FD_ISEDITABLE,    // FIELD_ADRACKReq
    };
    return (field >= 0 && field < 7) ? fieldTypeFlags[field] : 0;
}

const char *LoRaOptionsDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "LoRaTP",
        "LoRaCF",
        "LoRaSF",
        "LoRaBW",
        "LoRaCR",
        "UseHeader",
        "ADRACKReq",
    };
    return (field >= 0 && field < 7) ? fieldNames[field] : nullptr;
}

int LoRaOptionsDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "LoRaTP") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "LoRaCF") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "LoRaSF") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "LoRaBW") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "LoRaCR") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "UseHeader") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "ADRACKReq") == 0) return baseIndex + 6;
    return base ? base->findField(fieldName) : -1;
}

const char *LoRaOptionsDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "double",    // FIELD_LoRaTP
        "double",    // FIELD_LoRaCF
        "int",    // FIELD_LoRaSF
        "double",    // FIELD_LoRaBW
        "int",    // FIELD_LoRaCR
        "bool",    // FIELD_UseHeader
        "bool",    // FIELD_ADRACKReq
    };
    return (field >= 0 && field < 7) ? fieldTypeStrings[field] : nullptr;
}

const char **LoRaOptionsDescriptor::getFieldPropertyNames(int field) const
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

const char *LoRaOptionsDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int LoRaOptionsDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    LoRaOptions *pp = omnetpp::fromAnyPtr<LoRaOptions>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void LoRaOptionsDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    LoRaOptions *pp = omnetpp::fromAnyPtr<LoRaOptions>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'LoRaOptions'", field);
    }
}

const char *LoRaOptionsDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    LoRaOptions *pp = omnetpp::fromAnyPtr<LoRaOptions>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string LoRaOptionsDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    LoRaOptions *pp = omnetpp::fromAnyPtr<LoRaOptions>(object); (void)pp;
    switch (field) {
        case FIELD_LoRaTP: return double2string(pp->getLoRaTP());
        case FIELD_LoRaCF: return double2string(pp->getLoRaCF());
        case FIELD_LoRaSF: return long2string(pp->getLoRaSF());
        case FIELD_LoRaBW: return double2string(pp->getLoRaBW());
        case FIELD_LoRaCR: return long2string(pp->getLoRaCR());
        case FIELD_UseHeader: return bool2string(pp->getUseHeader());
        case FIELD_ADRACKReq: return bool2string(pp->getADRACKReq());
        default: return "";
    }
}

void LoRaOptionsDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LoRaOptions *pp = omnetpp::fromAnyPtr<LoRaOptions>(object); (void)pp;
    switch (field) {
        case FIELD_LoRaTP: pp->setLoRaTP(string2double(value)); break;
        case FIELD_LoRaCF: pp->setLoRaCF(string2double(value)); break;
        case FIELD_LoRaSF: pp->setLoRaSF(string2long(value)); break;
        case FIELD_LoRaBW: pp->setLoRaBW(string2double(value)); break;
        case FIELD_LoRaCR: pp->setLoRaCR(string2long(value)); break;
        case FIELD_UseHeader: pp->setUseHeader(string2bool(value)); break;
        case FIELD_ADRACKReq: pp->setADRACKReq(string2bool(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LoRaOptions'", field);
    }
}

omnetpp::cValue LoRaOptionsDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    LoRaOptions *pp = omnetpp::fromAnyPtr<LoRaOptions>(object); (void)pp;
    switch (field) {
        case FIELD_LoRaTP: return pp->getLoRaTP();
        case FIELD_LoRaCF: return pp->getLoRaCF();
        case FIELD_LoRaSF: return pp->getLoRaSF();
        case FIELD_LoRaBW: return pp->getLoRaBW();
        case FIELD_LoRaCR: return pp->getLoRaCR();
        case FIELD_UseHeader: return pp->getUseHeader();
        case FIELD_ADRACKReq: return pp->getADRACKReq();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'LoRaOptions' as cValue -- field index out of range?", field);
    }
}

void LoRaOptionsDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LoRaOptions *pp = omnetpp::fromAnyPtr<LoRaOptions>(object); (void)pp;
    switch (field) {
        case FIELD_LoRaTP: pp->setLoRaTP(value.doubleValue()); break;
        case FIELD_LoRaCF: pp->setLoRaCF(value.doubleValue()); break;
        case FIELD_LoRaSF: pp->setLoRaSF(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_LoRaBW: pp->setLoRaBW(value.doubleValue()); break;
        case FIELD_LoRaCR: pp->setLoRaCR(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_UseHeader: pp->setUseHeader(value.boolValue()); break;
        case FIELD_ADRACKReq: pp->setADRACKReq(value.boolValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LoRaOptions'", field);
    }
}

const char *LoRaOptionsDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr LoRaOptionsDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    LoRaOptions *pp = omnetpp::fromAnyPtr<LoRaOptions>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void LoRaOptionsDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    LoRaOptions *pp = omnetpp::fromAnyPtr<LoRaOptions>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LoRaOptions'", field);
    }
}

Register_Class(LoRaAppPacket)

LoRaAppPacket::LoRaAppPacket() : ::inet::FieldsChunk()
{
}

LoRaAppPacket::LoRaAppPacket(const LoRaAppPacket& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

LoRaAppPacket::~LoRaAppPacket()
{
}

LoRaAppPacket& LoRaAppPacket::operator=(const LoRaAppPacket& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void LoRaAppPacket::copy(const LoRaAppPacket& other)
{
    this->msgType = other.msgType;
    this->sampleMeasurement = other.sampleMeasurement;
    this->options = other.options;
}

void LoRaAppPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->msgType);
    doParsimPacking(b,this->sampleMeasurement);
    doParsimPacking(b,this->options);
}

void LoRaAppPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->msgType);
    doParsimUnpacking(b,this->sampleMeasurement);
    doParsimUnpacking(b,this->options);
}

int LoRaAppPacket::getMsgType() const
{
    return this->msgType;
}

void LoRaAppPacket::setMsgType(int msgType)
{
    handleChange();
    this->msgType = msgType;
}

int LoRaAppPacket::getSampleMeasurement() const
{
    return this->sampleMeasurement;
}

void LoRaAppPacket::setSampleMeasurement(int sampleMeasurement)
{
    handleChange();
    this->sampleMeasurement = sampleMeasurement;
}

const LoRaOptions& LoRaAppPacket::getOptions() const
{
    return this->options;
}

void LoRaAppPacket::setOptions(const LoRaOptions& options)
{
    handleChange();
    this->options = options;
}

class LoRaAppPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_msgType,
        FIELD_sampleMeasurement,
        FIELD_options,
    };
  public:
    LoRaAppPacketDescriptor();
    virtual ~LoRaAppPacketDescriptor();

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

Register_ClassDescriptor(LoRaAppPacketDescriptor)

LoRaAppPacketDescriptor::LoRaAppPacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::LoRaAppPacket)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

LoRaAppPacketDescriptor::~LoRaAppPacketDescriptor()
{
    delete[] propertyNames;
}

bool LoRaAppPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<LoRaAppPacket *>(obj)!=nullptr;
}

const char **LoRaAppPacketDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *LoRaAppPacketDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int LoRaAppPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int LoRaAppPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_msgType
        FD_ISEDITABLE,    // FIELD_sampleMeasurement
        FD_ISCOMPOUND,    // FIELD_options
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *LoRaAppPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "msgType",
        "sampleMeasurement",
        "options",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int LoRaAppPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "msgType") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "sampleMeasurement") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "options") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *LoRaAppPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_msgType
        "int",    // FIELD_sampleMeasurement
        "inet::LoRaOptions",    // FIELD_options
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **LoRaAppPacketDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_msgType: {
            static const char *names[] = { "enum", "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *LoRaAppPacketDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_msgType:
            if (!strcmp(propertyName, "enum")) return "AppPacketType";
            if (!strcmp(propertyName, "enum")) return "inet::AppPacketType";
            return nullptr;
        default: return nullptr;
    }
}

int LoRaAppPacketDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    LoRaAppPacket *pp = omnetpp::fromAnyPtr<LoRaAppPacket>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void LoRaAppPacketDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    LoRaAppPacket *pp = omnetpp::fromAnyPtr<LoRaAppPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'LoRaAppPacket'", field);
    }
}

const char *LoRaAppPacketDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    LoRaAppPacket *pp = omnetpp::fromAnyPtr<LoRaAppPacket>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string LoRaAppPacketDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    LoRaAppPacket *pp = omnetpp::fromAnyPtr<LoRaAppPacket>(object); (void)pp;
    switch (field) {
        case FIELD_msgType: return enum2string(pp->getMsgType(), "inet::AppPacketType");
        case FIELD_sampleMeasurement: return long2string(pp->getSampleMeasurement());
        case FIELD_options: return "";
        default: return "";
    }
}

void LoRaAppPacketDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LoRaAppPacket *pp = omnetpp::fromAnyPtr<LoRaAppPacket>(object); (void)pp;
    switch (field) {
        case FIELD_msgType: pp->setMsgType((inet::AppPacketType)string2enum(value, "inet::AppPacketType")); break;
        case FIELD_sampleMeasurement: pp->setSampleMeasurement(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LoRaAppPacket'", field);
    }
}

omnetpp::cValue LoRaAppPacketDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    LoRaAppPacket *pp = omnetpp::fromAnyPtr<LoRaAppPacket>(object); (void)pp;
    switch (field) {
        case FIELD_msgType: return pp->getMsgType();
        case FIELD_sampleMeasurement: return pp->getSampleMeasurement();
        case FIELD_options: return omnetpp::toAnyPtr(&pp->getOptions()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'LoRaAppPacket' as cValue -- field index out of range?", field);
    }
}

void LoRaAppPacketDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LoRaAppPacket *pp = omnetpp::fromAnyPtr<LoRaAppPacket>(object); (void)pp;
    switch (field) {
        case FIELD_msgType: pp->setMsgType((inet::AppPacketType)value.intValue()); break;
        case FIELD_sampleMeasurement: pp->setSampleMeasurement(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LoRaAppPacket'", field);
    }
}

const char *LoRaAppPacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_options: return omnetpp::opp_typename(typeid(LoRaOptions));
        default: return nullptr;
    };
}

omnetpp::any_ptr LoRaAppPacketDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    LoRaAppPacket *pp = omnetpp::fromAnyPtr<LoRaAppPacket>(object); (void)pp;
    switch (field) {
        case FIELD_options: return omnetpp::toAnyPtr(&pp->getOptions()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void LoRaAppPacketDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    LoRaAppPacket *pp = omnetpp::fromAnyPtr<LoRaAppPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LoRaAppPacket'", field);
    }
}

}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

