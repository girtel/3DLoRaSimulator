//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/LoRa/LoRaTagInfo.msg.
//

#ifndef __INET_LORATAGINFO_M_H
#define __INET_LORATAGINFO_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// opp_msgtool version check
#define MSGC_VERSION 0x0600
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgtool: 'make clean' should help.
#endif

// dll export symbol
#ifndef INET_API
#  if defined(INET_EXPORT)
#    define INET_API  OPP_DLLEXPORT
#  elif defined(INET_IMPORT)
#    define INET_API  OPP_DLLIMPORT
#  else
#    define INET_API
#  endif
#endif


namespace inet {

class LoRaTag;

}  // namespace inet

#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/common/TagBase_m.h" // import inet.common.TagBase

#include "inet/common/Units_m.h" // import inet.common.Units

#include "inet/linklayer/common/MacAddress_m.h" // import inet.linklayer.common.MacAddress

// cplusplus {{
using namespace inet;
// }}


namespace inet {

/**
 * Class generated from <tt>inet/LoRa/LoRaTagInfo.msg:28</tt> by opp_msgtool.
 * <pre>
 * class LoRaTag extends inet::TagBase
 * {
 *     inet::Hz centerFrequency = MHz(812);
 *     inet::Hz bandwidth = kHz(125);
 *     int spreadFactor = 12;
 *     inet::W power = mW(100);
 *     bool UseHeader = true;
 *     int codeRendundance = 1;
 * }
 * </pre>
 */
class INET_API LoRaTag : public ::inet::TagBase
{
  protected:
    Hz centerFrequency = MHz(812);
    Hz bandwidth = kHz(125);
    int spreadFactor = 12;
    W power = mW(100);
    bool UseHeader = true;
    int codeRendundance = 1;

  private:
    void copy(const LoRaTag& other);

  protected:
    bool operator==(const LoRaTag&) = delete;

  public:
    LoRaTag();
    LoRaTag(const LoRaTag& other);
    virtual ~LoRaTag();
    LoRaTag& operator=(const LoRaTag& other);
    virtual LoRaTag *dup() const override {return new LoRaTag(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual Hz getCenterFrequency() const;
    virtual void setCenterFrequency(Hz centerFrequency);

    virtual Hz getBandwidth() const;
    virtual void setBandwidth(Hz bandwidth);

    virtual int getSpreadFactor() const;
    virtual void setSpreadFactor(int spreadFactor);

    virtual W getPower() const;
    virtual void setPower(W power);

    virtual bool getUseHeader() const;
    virtual void setUseHeader(bool UseHeader);

    virtual int getCodeRendundance() const;
    virtual void setCodeRendundance(int codeRendundance);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const LoRaTag& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, LoRaTag& obj) {obj.parsimUnpack(b);}


}  // namespace inet


namespace omnetpp {

template<> inline inet::LoRaTag *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::LoRaTag*>(ptr.get<cObject>()); }

}  // namespace omnetpp

#endif // ifndef __INET_LORATAGINFO_M_H

