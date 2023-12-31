//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/LoRa/LoRaMacControlInfo.msg.
//

#ifndef __INET_LORAMACCONTROLINFO_M_H
#define __INET_LORAMACCONTROLINFO_M_H

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

class LoRaMacControlInfo;

}  // namespace inet

#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/common/Units_m.h" // import inet.common.Units

#include "inet/linklayer/common/MacAddress_m.h" // import inet.linklayer.common.MacAddress


namespace inet {

// cplusplus {{
using namespace inet;
// }}

/**
 * Class generated from <tt>inet/LoRa/LoRaMacControlInfo.msg:30</tt> by opp_msgtool.
 * <pre>
 * class LoRaMacControlInfo
 * {
 *     inet::MacAddress src;  // src DevAddr address (can be left empty when sending)
 *     inet::MacAddress dest; // dest DevAddr address
 * 
 *     double LoRaTP;
 *     inet::Hz LoRaCF;
 *     int LoRaSF;
 *     inet::Hz LoRaBW;
 *     int LoRaCR;
 *     bool LoRaUseHeader;
 * }
 * </pre>
 */
class INET_API LoRaMacControlInfo
{
  protected:
    MacAddress src;
    MacAddress dest;
    double LoRaTP = 0;
    Hz LoRaCF = Hz(NaN);
    int LoRaSF = 0;
    Hz LoRaBW = Hz(NaN);
    int LoRaCR = 0;
    bool LoRaUseHeader = false;

  private:
    void copy(const LoRaMacControlInfo& other);

  protected:
    bool operator==(const LoRaMacControlInfo&) = delete;

  public:
    LoRaMacControlInfo();
    LoRaMacControlInfo(const LoRaMacControlInfo& other);
    virtual ~LoRaMacControlInfo();
    LoRaMacControlInfo& operator=(const LoRaMacControlInfo& other);
    virtual void parsimPack(omnetpp::cCommBuffer *b) const;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b);

    virtual const MacAddress& getSrc() const;
    virtual MacAddress& getSrcForUpdate() { return const_cast<MacAddress&>(const_cast<LoRaMacControlInfo*>(this)->getSrc());}
    virtual void setSrc(const MacAddress& src);

    virtual const MacAddress& getDest() const;
    virtual MacAddress& getDestForUpdate() { return const_cast<MacAddress&>(const_cast<LoRaMacControlInfo*>(this)->getDest());}
    virtual void setDest(const MacAddress& dest);

    virtual double getLoRaTP() const;
    virtual void setLoRaTP(double LoRaTP);

    virtual Hz getLoRaCF() const;
    virtual void setLoRaCF(Hz LoRaCF);

    virtual int getLoRaSF() const;
    virtual void setLoRaSF(int LoRaSF);

    virtual Hz getLoRaBW() const;
    virtual void setLoRaBW(Hz LoRaBW);

    virtual int getLoRaCR() const;
    virtual void setLoRaCR(int LoRaCR);

    virtual bool getLoRaUseHeader() const;
    virtual void setLoRaUseHeader(bool LoRaUseHeader);
};


}  // namespace inet


namespace omnetpp {

inline any_ptr toAnyPtr(const inet::LoRaMacControlInfo *p) {if (auto obj = as_cObject(p)) return any_ptr(obj); else return any_ptr(p);}
template<> inline inet::LoRaMacControlInfo *fromAnyPtr(any_ptr ptr) { return ptr.get<inet::LoRaMacControlInfo>(); }

}  // namespace omnetpp

#endif // ifndef __INET_LORAMACCONTROLINFO_M_H

