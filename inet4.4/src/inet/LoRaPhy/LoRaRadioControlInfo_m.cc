//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/LoRaPhy/LoRaRadioControlInfo.msg.
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
#include "LoRaRadioControlInfo_m.h"

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

Register_Enum(inet::LoRaRadioCommandCode, (inet::LoRaRadioCommandCode::LORA_RADIO_C_CONFIGURE));

LoRaConfigureRadioCommand::LoRaConfigureRadioCommand()
{
}

LoRaConfigureRadioCommand::LoRaConfigureRadioCommand(const LoRaConfigureRadioCommand& other)
{
    copy(other);
}

LoRaConfigureRadioCommand::~LoRaConfigureRadioCommand()
{
}

LoRaConfigureRadioCommand& LoRaConfigureRadioCommand::operator=(const LoRaConfigureRadioCommand& other)
{
    if (this == &other) return *this;
    copy(other);
    return *this;
}

void LoRaConfigureRadioCommand::copy(const LoRaConfigureRadioCommand& other)
{
    this->radioMode = other.radioMode;
    this->power = other.power;
    this->bitrate = other.bitrate;
    this->carrierFrequency = other.carrierFrequency;
    this->bandwidth = other.bandwidth;
}

void LoRaConfigureRadioCommand::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->radioMode);
    doParsimPacking(b,this->power);
    doParsimPacking(b,this->bitrate);
    doParsimPacking(b,this->carrierFrequency);
    doParsimPacking(b,this->bandwidth);
}

void LoRaConfigureRadioCommand::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->radioMode);
    doParsimUnpacking(b,this->power);
    doParsimUnpacking(b,this->bitrate);
    doParsimUnpacking(b,this->carrierFrequency);
    doParsimUnpacking(b,this->bandwidth);
}

int LoRaConfigureRadioCommand::getRadioMode() const
{
    return this->radioMode;
}

void LoRaConfigureRadioCommand::setRadioMode(int radioMode)
{
    this->radioMode = radioMode;
}

W LoRaConfigureRadioCommand::getPower() const
{
    return this->power;
}

void LoRaConfigureRadioCommand::setPower(W power)
{
    this->power = power;
}

bps LoRaConfigureRadioCommand::getBitrate() const
{
    return this->bitrate;
}

void LoRaConfigureRadioCommand::setBitrate(bps bitrate)
{
    this->bitrate = bitrate;
}

Hz LoRaConfigureRadioCommand::getCarrierFrequency() const
{
    return this->carrierFrequency;
}

void LoRaConfigureRadioCommand::setCarrierFrequency(Hz carrierFrequency)
{
    this->carrierFrequency = carrierFrequency;
}

Hz LoRaConfigureRadioCommand::getBandwidth() const
{
    return this->bandwidth;
}

void LoRaConfigureRadioCommand::setBandwidth(Hz bandwidth)
{
    this->bandwidth = bandwidth;
}

class LoRaConfigureRadioCommandDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_radioMode,
        FIELD_power,
        FIELD_bitrate,
        FIELD_carrierFrequency,
        FIELD_bandwidth,
    };
  public:
    LoRaConfigureRadioCommandDescriptor();
    virtual ~LoRaConfigureRadioCommandDescriptor();

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

Register_ClassDescriptor(LoRaConfigureRadioCommandDescriptor)

LoRaConfigureRadioCommandDescriptor::LoRaConfigureRadioCommandDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::LoRaConfigureRadioCommand)), "")
{
    propertyNames = nullptr;
}

LoRaConfigureRadioCommandDescriptor::~LoRaConfigureRadioCommandDescriptor()
{
    delete[] propertyNames;
}

bool LoRaConfigureRadioCommandDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<LoRaConfigureRadioCommand *>(obj)!=nullptr;
}

const char **LoRaConfigureRadioCommandDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *LoRaConfigureRadioCommandDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int LoRaConfigureRadioCommandDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int LoRaConfigureRadioCommandDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_radioMode
        FD_ISEDITABLE,    // FIELD_power
        FD_ISEDITABLE,    // FIELD_bitrate
        FD_ISEDITABLE,    // FIELD_carrierFrequency
        FD_ISEDITABLE,    // FIELD_bandwidth
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *LoRaConfigureRadioCommandDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "radioMode",
        "power",
        "bitrate",
        "carrierFrequency",
        "bandwidth",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int LoRaConfigureRadioCommandDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "radioMode") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "power") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "bitrate") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "carrierFrequency") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "bandwidth") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *LoRaConfigureRadioCommandDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_radioMode
        "inet::W",    // FIELD_power
        "inet::bps",    // FIELD_bitrate
        "inet::Hz",    // FIELD_carrierFrequency
        "inet::Hz",    // FIELD_bandwidth
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **LoRaConfigureRadioCommandDescriptor::getFieldPropertyNames(int field) const
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

const char *LoRaConfigureRadioCommandDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int LoRaConfigureRadioCommandDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    LoRaConfigureRadioCommand *pp = omnetpp::fromAnyPtr<LoRaConfigureRadioCommand>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void LoRaConfigureRadioCommandDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    LoRaConfigureRadioCommand *pp = omnetpp::fromAnyPtr<LoRaConfigureRadioCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'LoRaConfigureRadioCommand'", field);
    }
}

const char *LoRaConfigureRadioCommandDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    LoRaConfigureRadioCommand *pp = omnetpp::fromAnyPtr<LoRaConfigureRadioCommand>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string LoRaConfigureRadioCommandDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    LoRaConfigureRadioCommand *pp = omnetpp::fromAnyPtr<LoRaConfigureRadioCommand>(object); (void)pp;
    switch (field) {
        case FIELD_radioMode: return long2string(pp->getRadioMode());
        case FIELD_power: return unit2string(pp->getPower());
        case FIELD_bitrate: return unit2string(pp->getBitrate());
        case FIELD_carrierFrequency: return unit2string(pp->getCarrierFrequency());
        case FIELD_bandwidth: return unit2string(pp->getBandwidth());
        default: return "";
    }
}

void LoRaConfigureRadioCommandDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LoRaConfigureRadioCommand *pp = omnetpp::fromAnyPtr<LoRaConfigureRadioCommand>(object); (void)pp;
    switch (field) {
        case FIELD_radioMode: pp->setRadioMode(string2long(value)); break;
        case FIELD_power: pp->setPower(W(string2double(value))); break;
        case FIELD_bitrate: pp->setBitrate(bps(string2double(value))); break;
        case FIELD_carrierFrequency: pp->setCarrierFrequency(Hz(string2double(value))); break;
        case FIELD_bandwidth: pp->setBandwidth(Hz(string2double(value))); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LoRaConfigureRadioCommand'", field);
    }
}

omnetpp::cValue LoRaConfigureRadioCommandDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    LoRaConfigureRadioCommand *pp = omnetpp::fromAnyPtr<LoRaConfigureRadioCommand>(object); (void)pp;
    switch (field) {
        case FIELD_radioMode: return pp->getRadioMode();
        case FIELD_power: return cValue(pp->getPower().get(),"W");
        case FIELD_bitrate: return cValue(pp->getBitrate().get(),"bps");
        case FIELD_carrierFrequency: return cValue(pp->getCarrierFrequency().get(),"Hz");
        case FIELD_bandwidth: return cValue(pp->getBandwidth().get(),"Hz");
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'LoRaConfigureRadioCommand' as cValue -- field index out of range?", field);
    }
}

void LoRaConfigureRadioCommandDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LoRaConfigureRadioCommand *pp = omnetpp::fromAnyPtr<LoRaConfigureRadioCommand>(object); (void)pp;
    switch (field) {
        case FIELD_radioMode: pp->setRadioMode(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_power: pp->setPower(W(value.doubleValueInUnit("W"))); break;
        case FIELD_bitrate: pp->setBitrate(bps(value.doubleValueInUnit("bps"))); break;
        case FIELD_carrierFrequency: pp->setCarrierFrequency(Hz(value.doubleValueInUnit("Hz"))); break;
        case FIELD_bandwidth: pp->setBandwidth(Hz(value.doubleValueInUnit("Hz"))); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LoRaConfigureRadioCommand'", field);
    }
}

const char *LoRaConfigureRadioCommandDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr LoRaConfigureRadioCommandDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    LoRaConfigureRadioCommand *pp = omnetpp::fromAnyPtr<LoRaConfigureRadioCommand>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void LoRaConfigureRadioCommandDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    LoRaConfigureRadioCommand *pp = omnetpp::fromAnyPtr<LoRaConfigureRadioCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LoRaConfigureRadioCommand'", field);
    }
}

LoRaTransmissionRequest::LoRaTransmissionRequest()
{
}

LoRaTransmissionRequest::LoRaTransmissionRequest(const LoRaTransmissionRequest& other)
{
    copy(other);
}

LoRaTransmissionRequest::~LoRaTransmissionRequest()
{
}

LoRaTransmissionRequest& LoRaTransmissionRequest::operator=(const LoRaTransmissionRequest& other)
{
    if (this == &other) return *this;
    copy(other);
    return *this;
}

void LoRaTransmissionRequest::copy(const LoRaTransmissionRequest& other)
{
    this->power = other.power;
    this->bitrate = other.bitrate;
    this->carrierFrequency = other.carrierFrequency;
    this->bandwidth = other.bandwidth;
}

void LoRaTransmissionRequest::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->power);
    doParsimPacking(b,this->bitrate);
    doParsimPacking(b,this->carrierFrequency);
    doParsimPacking(b,this->bandwidth);
}

void LoRaTransmissionRequest::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->power);
    doParsimUnpacking(b,this->bitrate);
    doParsimUnpacking(b,this->carrierFrequency);
    doParsimUnpacking(b,this->bandwidth);
}

W LoRaTransmissionRequest::getPower() const
{
    return this->power;
}

void LoRaTransmissionRequest::setPower(W power)
{
    this->power = power;
}

bps LoRaTransmissionRequest::getBitrate() const
{
    return this->bitrate;
}

void LoRaTransmissionRequest::setBitrate(bps bitrate)
{
    this->bitrate = bitrate;
}

Hz LoRaTransmissionRequest::getCarrierFrequency() const
{
    return this->carrierFrequency;
}

void LoRaTransmissionRequest::setCarrierFrequency(Hz carrierFrequency)
{
    this->carrierFrequency = carrierFrequency;
}

Hz LoRaTransmissionRequest::getBandwidth() const
{
    return this->bandwidth;
}

void LoRaTransmissionRequest::setBandwidth(Hz bandwidth)
{
    this->bandwidth = bandwidth;
}

class LoRaTransmissionRequestDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_power,
        FIELD_bitrate,
        FIELD_carrierFrequency,
        FIELD_bandwidth,
    };
  public:
    LoRaTransmissionRequestDescriptor();
    virtual ~LoRaTransmissionRequestDescriptor();

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

Register_ClassDescriptor(LoRaTransmissionRequestDescriptor)

LoRaTransmissionRequestDescriptor::LoRaTransmissionRequestDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::LoRaTransmissionRequest)), "")
{
    propertyNames = nullptr;
}

LoRaTransmissionRequestDescriptor::~LoRaTransmissionRequestDescriptor()
{
    delete[] propertyNames;
}

bool LoRaTransmissionRequestDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<LoRaTransmissionRequest *>(obj)!=nullptr;
}

const char **LoRaTransmissionRequestDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *LoRaTransmissionRequestDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int LoRaTransmissionRequestDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int LoRaTransmissionRequestDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_power
        FD_ISEDITABLE,    // FIELD_bitrate
        FD_ISEDITABLE,    // FIELD_carrierFrequency
        FD_ISEDITABLE,    // FIELD_bandwidth
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *LoRaTransmissionRequestDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "power",
        "bitrate",
        "carrierFrequency",
        "bandwidth",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int LoRaTransmissionRequestDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "power") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "bitrate") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "carrierFrequency") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "bandwidth") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *LoRaTransmissionRequestDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::W",    // FIELD_power
        "inet::bps",    // FIELD_bitrate
        "inet::Hz",    // FIELD_carrierFrequency
        "inet::Hz",    // FIELD_bandwidth
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **LoRaTransmissionRequestDescriptor::getFieldPropertyNames(int field) const
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

const char *LoRaTransmissionRequestDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int LoRaTransmissionRequestDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    LoRaTransmissionRequest *pp = omnetpp::fromAnyPtr<LoRaTransmissionRequest>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void LoRaTransmissionRequestDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    LoRaTransmissionRequest *pp = omnetpp::fromAnyPtr<LoRaTransmissionRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'LoRaTransmissionRequest'", field);
    }
}

const char *LoRaTransmissionRequestDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    LoRaTransmissionRequest *pp = omnetpp::fromAnyPtr<LoRaTransmissionRequest>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string LoRaTransmissionRequestDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    LoRaTransmissionRequest *pp = omnetpp::fromAnyPtr<LoRaTransmissionRequest>(object); (void)pp;
    switch (field) {
        case FIELD_power: return unit2string(pp->getPower());
        case FIELD_bitrate: return unit2string(pp->getBitrate());
        case FIELD_carrierFrequency: return unit2string(pp->getCarrierFrequency());
        case FIELD_bandwidth: return unit2string(pp->getBandwidth());
        default: return "";
    }
}

void LoRaTransmissionRequestDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LoRaTransmissionRequest *pp = omnetpp::fromAnyPtr<LoRaTransmissionRequest>(object); (void)pp;
    switch (field) {
        case FIELD_power: pp->setPower(W(string2double(value))); break;
        case FIELD_bitrate: pp->setBitrate(bps(string2double(value))); break;
        case FIELD_carrierFrequency: pp->setCarrierFrequency(Hz(string2double(value))); break;
        case FIELD_bandwidth: pp->setBandwidth(Hz(string2double(value))); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LoRaTransmissionRequest'", field);
    }
}

omnetpp::cValue LoRaTransmissionRequestDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    LoRaTransmissionRequest *pp = omnetpp::fromAnyPtr<LoRaTransmissionRequest>(object); (void)pp;
    switch (field) {
        case FIELD_power: return cValue(pp->getPower().get(),"W");
        case FIELD_bitrate: return cValue(pp->getBitrate().get(),"bps");
        case FIELD_carrierFrequency: return cValue(pp->getCarrierFrequency().get(),"Hz");
        case FIELD_bandwidth: return cValue(pp->getBandwidth().get(),"Hz");
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'LoRaTransmissionRequest' as cValue -- field index out of range?", field);
    }
}

void LoRaTransmissionRequestDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LoRaTransmissionRequest *pp = omnetpp::fromAnyPtr<LoRaTransmissionRequest>(object); (void)pp;
    switch (field) {
        case FIELD_power: pp->setPower(W(value.doubleValueInUnit("W"))); break;
        case FIELD_bitrate: pp->setBitrate(bps(value.doubleValueInUnit("bps"))); break;
        case FIELD_carrierFrequency: pp->setCarrierFrequency(Hz(value.doubleValueInUnit("Hz"))); break;
        case FIELD_bandwidth: pp->setBandwidth(Hz(value.doubleValueInUnit("Hz"))); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LoRaTransmissionRequest'", field);
    }
}

const char *LoRaTransmissionRequestDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr LoRaTransmissionRequestDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    LoRaTransmissionRequest *pp = omnetpp::fromAnyPtr<LoRaTransmissionRequest>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void LoRaTransmissionRequestDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    LoRaTransmissionRequest *pp = omnetpp::fromAnyPtr<LoRaTransmissionRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LoRaTransmissionRequest'", field);
    }
}

LoRaReceptionIndication::LoRaReceptionIndication()
{
}

LoRaReceptionIndication::LoRaReceptionIndication(const LoRaReceptionIndication& other)
{
    copy(other);
}

LoRaReceptionIndication::~LoRaReceptionIndication()
{
}

LoRaReceptionIndication& LoRaReceptionIndication::operator=(const LoRaReceptionIndication& other)
{
    if (this == &other) return *this;
    copy(other);
    return *this;
}

void LoRaReceptionIndication::copy(const LoRaReceptionIndication& other)
{
    this->minRSSI = other.minRSSI;
    this->minSNIR = other.minSNIR;
    this->LoRaTP = other.LoRaTP;
    this->LoRaCF = other.LoRaCF;
    this->LoRaSF = other.LoRaSF;
    this->LoRaBW = other.LoRaBW;
    this->LoRaCR = other.LoRaCR;
}

void LoRaReceptionIndication::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->minRSSI);
    doParsimPacking(b,this->minSNIR);
    doParsimPacking(b,this->LoRaTP);
    doParsimPacking(b,this->LoRaCF);
    doParsimPacking(b,this->LoRaSF);
    doParsimPacking(b,this->LoRaBW);
    doParsimPacking(b,this->LoRaCR);
}

void LoRaReceptionIndication::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->minRSSI);
    doParsimUnpacking(b,this->minSNIR);
    doParsimUnpacking(b,this->LoRaTP);
    doParsimUnpacking(b,this->LoRaCF);
    doParsimUnpacking(b,this->LoRaSF);
    doParsimUnpacking(b,this->LoRaBW);
    doParsimUnpacking(b,this->LoRaCR);
}

W LoRaReceptionIndication::getMinRSSI() const
{
    return this->minRSSI;
}

void LoRaReceptionIndication::setMinRSSI(W minRSSI)
{
    this->minRSSI = minRSSI;
}

double LoRaReceptionIndication::getMinSNIR() const
{
    return this->minSNIR;
}

void LoRaReceptionIndication::setMinSNIR(double minSNIR)
{
    this->minSNIR = minSNIR;
}

W LoRaReceptionIndication::getLoRaTP() const
{
    return this->LoRaTP;
}

void LoRaReceptionIndication::setLoRaTP(W LoRaTP)
{
    this->LoRaTP = LoRaTP;
}

Hz LoRaReceptionIndication::getLoRaCF() const
{
    return this->LoRaCF;
}

void LoRaReceptionIndication::setLoRaCF(Hz LoRaCF)
{
    this->LoRaCF = LoRaCF;
}

int LoRaReceptionIndication::getLoRaSF() const
{
    return this->LoRaSF;
}

void LoRaReceptionIndication::setLoRaSF(int LoRaSF)
{
    this->LoRaSF = LoRaSF;
}

Hz LoRaReceptionIndication::getLoRaBW() const
{
    return this->LoRaBW;
}

void LoRaReceptionIndication::setLoRaBW(Hz LoRaBW)
{
    this->LoRaBW = LoRaBW;
}

int LoRaReceptionIndication::getLoRaCR() const
{
    return this->LoRaCR;
}

void LoRaReceptionIndication::setLoRaCR(int LoRaCR)
{
    this->LoRaCR = LoRaCR;
}

class LoRaReceptionIndicationDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_minRSSI,
        FIELD_minSNIR,
        FIELD_LoRaTP,
        FIELD_LoRaCF,
        FIELD_LoRaSF,
        FIELD_LoRaBW,
        FIELD_LoRaCR,
    };
  public:
    LoRaReceptionIndicationDescriptor();
    virtual ~LoRaReceptionIndicationDescriptor();

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

Register_ClassDescriptor(LoRaReceptionIndicationDescriptor)

LoRaReceptionIndicationDescriptor::LoRaReceptionIndicationDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::LoRaReceptionIndication)), "")
{
    propertyNames = nullptr;
}

LoRaReceptionIndicationDescriptor::~LoRaReceptionIndicationDescriptor()
{
    delete[] propertyNames;
}

bool LoRaReceptionIndicationDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<LoRaReceptionIndication *>(obj)!=nullptr;
}

const char **LoRaReceptionIndicationDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *LoRaReceptionIndicationDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int LoRaReceptionIndicationDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 7+base->getFieldCount() : 7;
}

unsigned int LoRaReceptionIndicationDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_minRSSI
        FD_ISEDITABLE,    // FIELD_minSNIR
        FD_ISEDITABLE,    // FIELD_LoRaTP
        FD_ISEDITABLE,    // FIELD_LoRaCF
        FD_ISEDITABLE,    // FIELD_LoRaSF
        FD_ISEDITABLE,    // FIELD_LoRaBW
        FD_ISEDITABLE,    // FIELD_LoRaCR
    };
    return (field >= 0 && field < 7) ? fieldTypeFlags[field] : 0;
}

const char *LoRaReceptionIndicationDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "minRSSI",
        "minSNIR",
        "LoRaTP",
        "LoRaCF",
        "LoRaSF",
        "LoRaBW",
        "LoRaCR",
    };
    return (field >= 0 && field < 7) ? fieldNames[field] : nullptr;
}

int LoRaReceptionIndicationDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "minRSSI") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "minSNIR") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "LoRaTP") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "LoRaCF") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "LoRaSF") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "LoRaBW") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "LoRaCR") == 0) return baseIndex + 6;
    return base ? base->findField(fieldName) : -1;
}

const char *LoRaReceptionIndicationDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::W",    // FIELD_minRSSI
        "double",    // FIELD_minSNIR
        "inet::W",    // FIELD_LoRaTP
        "inet::Hz",    // FIELD_LoRaCF
        "int",    // FIELD_LoRaSF
        "inet::Hz",    // FIELD_LoRaBW
        "int",    // FIELD_LoRaCR
    };
    return (field >= 0 && field < 7) ? fieldTypeStrings[field] : nullptr;
}

const char **LoRaReceptionIndicationDescriptor::getFieldPropertyNames(int field) const
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

const char *LoRaReceptionIndicationDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int LoRaReceptionIndicationDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    LoRaReceptionIndication *pp = omnetpp::fromAnyPtr<LoRaReceptionIndication>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void LoRaReceptionIndicationDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    LoRaReceptionIndication *pp = omnetpp::fromAnyPtr<LoRaReceptionIndication>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'LoRaReceptionIndication'", field);
    }
}

const char *LoRaReceptionIndicationDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    LoRaReceptionIndication *pp = omnetpp::fromAnyPtr<LoRaReceptionIndication>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string LoRaReceptionIndicationDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    LoRaReceptionIndication *pp = omnetpp::fromAnyPtr<LoRaReceptionIndication>(object); (void)pp;
    switch (field) {
        case FIELD_minRSSI: return unit2string(pp->getMinRSSI());
        case FIELD_minSNIR: return double2string(pp->getMinSNIR());
        case FIELD_LoRaTP: return unit2string(pp->getLoRaTP());
        case FIELD_LoRaCF: return unit2string(pp->getLoRaCF());
        case FIELD_LoRaSF: return long2string(pp->getLoRaSF());
        case FIELD_LoRaBW: return unit2string(pp->getLoRaBW());
        case FIELD_LoRaCR: return long2string(pp->getLoRaCR());
        default: return "";
    }
}

void LoRaReceptionIndicationDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LoRaReceptionIndication *pp = omnetpp::fromAnyPtr<LoRaReceptionIndication>(object); (void)pp;
    switch (field) {
        case FIELD_minRSSI: pp->setMinRSSI(W(string2double(value))); break;
        case FIELD_minSNIR: pp->setMinSNIR(string2double(value)); break;
        case FIELD_LoRaTP: pp->setLoRaTP(W(string2double(value))); break;
        case FIELD_LoRaCF: pp->setLoRaCF(Hz(string2double(value))); break;
        case FIELD_LoRaSF: pp->setLoRaSF(string2long(value)); break;
        case FIELD_LoRaBW: pp->setLoRaBW(Hz(string2double(value))); break;
        case FIELD_LoRaCR: pp->setLoRaCR(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LoRaReceptionIndication'", field);
    }
}

omnetpp::cValue LoRaReceptionIndicationDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    LoRaReceptionIndication *pp = omnetpp::fromAnyPtr<LoRaReceptionIndication>(object); (void)pp;
    switch (field) {
        case FIELD_minRSSI: return cValue(pp->getMinRSSI().get(),"W");
        case FIELD_minSNIR: return pp->getMinSNIR();
        case FIELD_LoRaTP: return cValue(pp->getLoRaTP().get(),"W");
        case FIELD_LoRaCF: return cValue(pp->getLoRaCF().get(),"Hz");
        case FIELD_LoRaSF: return pp->getLoRaSF();
        case FIELD_LoRaBW: return cValue(pp->getLoRaBW().get(),"Hz");
        case FIELD_LoRaCR: return pp->getLoRaCR();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'LoRaReceptionIndication' as cValue -- field index out of range?", field);
    }
}

void LoRaReceptionIndicationDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LoRaReceptionIndication *pp = omnetpp::fromAnyPtr<LoRaReceptionIndication>(object); (void)pp;
    switch (field) {
        case FIELD_minRSSI: pp->setMinRSSI(W(value.doubleValueInUnit("W"))); break;
        case FIELD_minSNIR: pp->setMinSNIR(value.doubleValue()); break;
        case FIELD_LoRaTP: pp->setLoRaTP(W(value.doubleValueInUnit("W"))); break;
        case FIELD_LoRaCF: pp->setLoRaCF(Hz(value.doubleValueInUnit("Hz"))); break;
        case FIELD_LoRaSF: pp->setLoRaSF(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_LoRaBW: pp->setLoRaBW(Hz(value.doubleValueInUnit("Hz"))); break;
        case FIELD_LoRaCR: pp->setLoRaCR(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LoRaReceptionIndication'", field);
    }
}

const char *LoRaReceptionIndicationDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr LoRaReceptionIndicationDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    LoRaReceptionIndication *pp = omnetpp::fromAnyPtr<LoRaReceptionIndication>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void LoRaReceptionIndicationDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    LoRaReceptionIndication *pp = omnetpp::fromAnyPtr<LoRaReceptionIndication>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LoRaReceptionIndication'", field);
    }
}

}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

