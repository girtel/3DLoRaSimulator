//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/physicallayer/wireless/ieee80211/packetlevel/Ieee80211ControlInfo.msg.
//

#ifndef __INET__PHYSICALLAYER_IEEE80211CONTROLINFO_M_H
#define __INET__PHYSICALLAYER_IEEE80211CONTROLINFO_M_H

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
namespace physicallayer {

class Ieee80211ConfigureRadioCommand;

}  // namespace physicallayer
}  // namespace inet

#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/common/Units_m.h" // import inet.common.Units

#include "inet/physicallayer/wireless/common/contract/packetlevel/RadioControlInfo_m.h" // import inet.physicallayer.wireless.common.contract.packetlevel.RadioControlInfo

#include "inet/physicallayer/wireless/ieee80211/mode/IIeee80211Mode_m.h" // import inet.physicallayer.wireless.ieee80211.mode.IIeee80211Mode

#include "inet/physicallayer/wireless/ieee80211/mode/Ieee80211Channel_m.h" // import inet.physicallayer.wireless.ieee80211.mode.Ieee80211Channel


namespace inet {
namespace physicallayer {

/**
 * Class generated from <tt>inet/physicallayer/wireless/ieee80211/packetlevel/Ieee80211ControlInfo.msg:19</tt> by opp_msgtool.
 * <pre>
 * //
 * // Control info attached to a configure command that is sent to the ~Radio.
 * //
 * class Ieee80211ConfigureRadioCommand extends ConfigureRadioCommand
 * {
 *     string opMode;                         // new default operation mode or "" if not set.
 *     const Ieee80211ModeSet *modeSet;       // new default mode set or nullptr if not set.
 *     const IIeee80211Mode *mode;            // new default transmission mode or nullptr if not set.
 *     IIeee80211Band *band;                  // new default band or nullptr if not set.
 *     Ieee80211Channel *channel;             // new default band and channel or nullptr if not set.
 *     int channelNumber = -1;                // new default channel number in the range [0, numChannels] or -1 if not set.
 * }
 * </pre>
 */
class INET_API Ieee80211ConfigureRadioCommand : public ::inet::physicallayer::ConfigureRadioCommand
{
  protected:
    ::omnetpp::opp_string opMode;
    const Ieee80211ModeSet * modeSet = nullptr;
    const IIeee80211Mode * mode = nullptr;
    IIeee80211Band * band = nullptr;
    Ieee80211Channel * channel = nullptr;
    int channelNumber = -1;

  private:
    void copy(const Ieee80211ConfigureRadioCommand& other);

  protected:
    bool operator==(const Ieee80211ConfigureRadioCommand&) = delete;

  public:
    Ieee80211ConfigureRadioCommand();
    Ieee80211ConfigureRadioCommand(const Ieee80211ConfigureRadioCommand& other);
    virtual ~Ieee80211ConfigureRadioCommand();
    Ieee80211ConfigureRadioCommand& operator=(const Ieee80211ConfigureRadioCommand& other);
    virtual Ieee80211ConfigureRadioCommand *dup() const override {return new Ieee80211ConfigureRadioCommand(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual const char * getOpMode() const;
    virtual void setOpMode(const char * opMode);

    virtual const Ieee80211ModeSet * getModeSet() const;
    virtual void setModeSet(const Ieee80211ModeSet * modeSet);

    virtual const IIeee80211Mode * getMode() const;
    virtual void setMode(const IIeee80211Mode * mode);

    virtual const IIeee80211Band * getBand() const;
    virtual IIeee80211Band * getBandForUpdate() { return const_cast<IIeee80211Band *>(const_cast<Ieee80211ConfigureRadioCommand*>(this)->getBand());}
    virtual void setBand(IIeee80211Band * band);

    virtual const Ieee80211Channel * getChannel() const;
    virtual Ieee80211Channel * getChannelForUpdate() { return const_cast<Ieee80211Channel *>(const_cast<Ieee80211ConfigureRadioCommand*>(this)->getChannel());}
    virtual void setChannel(Ieee80211Channel * channel);

    virtual int getChannelNumber() const;
    virtual void setChannelNumber(int channelNumber);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Ieee80211ConfigureRadioCommand& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Ieee80211ConfigureRadioCommand& obj) {obj.parsimUnpack(b);}


}  // namespace physicallayer
}  // namespace inet


namespace omnetpp {

template<> inline inet::physicallayer::Ieee80211ConfigureRadioCommand *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::physicallayer::Ieee80211ConfigureRadioCommand*>(ptr.get<cObject>()); }

}  // namespace omnetpp

#endif // ifndef __INET__PHYSICALLAYER_IEEE80211CONTROLINFO_M_H

