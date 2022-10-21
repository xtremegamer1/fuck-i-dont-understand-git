#include <vtil\vtil>
#include <Zydis\Zydis.h>

//TODO: make this suck less ass
//Also no, i did not write this by hand, I made a C util to do it for me since I don't know how to use regex or ahk etc
constexpr std::pair<ZydisRegister, x86_reg> zyreg_to_capreg_arr[]
{
  { ZYDIS_REGISTER_AL, X86_REG_AL },
  { ZYDIS_REGISTER_CL, X86_REG_CL },
  { ZYDIS_REGISTER_DL, X86_REG_DL },
  { ZYDIS_REGISTER_BL, X86_REG_BL },
  { ZYDIS_REGISTER_AH, X86_REG_AH },
  { ZYDIS_REGISTER_CH, X86_REG_CH },
  { ZYDIS_REGISTER_DH, X86_REG_DH },
  { ZYDIS_REGISTER_BH, X86_REG_BH },
  { ZYDIS_REGISTER_SPL, X86_REG_SPL },
  { ZYDIS_REGISTER_BPL, X86_REG_BPL },
  { ZYDIS_REGISTER_SIL, X86_REG_SIL },
  { ZYDIS_REGISTER_DIL, X86_REG_DIL },
  { ZYDIS_REGISTER_R8B, X86_REG_R8B },
  { ZYDIS_REGISTER_R9B, X86_REG_R9B },
  { ZYDIS_REGISTER_R10B, X86_REG_R10B },
  { ZYDIS_REGISTER_R11B, X86_REG_R11B },
  { ZYDIS_REGISTER_R12B, X86_REG_R12B },
  { ZYDIS_REGISTER_R13B, X86_REG_R13B },
  { ZYDIS_REGISTER_R14B, X86_REG_R14B },
  { ZYDIS_REGISTER_R15B, X86_REG_R15B },
  { ZYDIS_REGISTER_AX, X86_REG_AX },
  { ZYDIS_REGISTER_CX, X86_REG_CX },
  { ZYDIS_REGISTER_DX, X86_REG_DX },
  { ZYDIS_REGISTER_BX, X86_REG_BX },
  { ZYDIS_REGISTER_SP, X86_REG_SP },
  { ZYDIS_REGISTER_BP, X86_REG_BP },
  { ZYDIS_REGISTER_SI, X86_REG_SI },
  { ZYDIS_REGISTER_DI, X86_REG_DI },
  { ZYDIS_REGISTER_R8W, X86_REG_R8W },
  { ZYDIS_REGISTER_R9W, X86_REG_R9W },
  { ZYDIS_REGISTER_R10W, X86_REG_R10W },
  { ZYDIS_REGISTER_R11W, X86_REG_R11W },
  { ZYDIS_REGISTER_R12W, X86_REG_R12W },
  { ZYDIS_REGISTER_R13W, X86_REG_R13W },
  { ZYDIS_REGISTER_R14W, X86_REG_R14W },
  { ZYDIS_REGISTER_R15W, X86_REG_R15W },
  { ZYDIS_REGISTER_EAX, X86_REG_EAX },
  { ZYDIS_REGISTER_ECX, X86_REG_ECX },
  { ZYDIS_REGISTER_EBX, X86_REG_EBX },
  { ZYDIS_REGISTER_ESP, X86_REG_ESP },
  { ZYDIS_REGISTER_EBP, X86_REG_EBP },
  { ZYDIS_REGISTER_ESI, X86_REG_ESI },
  { ZYDIS_REGISTER_EDI, X86_REG_EDI },
  { ZYDIS_REGISTER_R8D, X86_REG_R8D },
  { ZYDIS_REGISTER_R9D, X86_REG_R9D },
  { ZYDIS_REGISTER_R10D, X86_REG_R10D },
  { ZYDIS_REGISTER_R11D, X86_REG_R11D },
  { ZYDIS_REGISTER_R12D, X86_REG_R12D },
  { ZYDIS_REGISTER_R13D, X86_REG_R13D },
  { ZYDIS_REGISTER_R14D, X86_REG_R14D },
  { ZYDIS_REGISTER_R15D, X86_REG_R15D },
  { ZYDIS_REGISTER_RAX, X86_REG_RAX },
  { ZYDIS_REGISTER_RCX, X86_REG_RCX },
  { ZYDIS_REGISTER_RDX, X86_REG_RDX },
  { ZYDIS_REGISTER_RBX, X86_REG_RBX },
  { ZYDIS_REGISTER_RSP, X86_REG_RSP },
  { ZYDIS_REGISTER_RBP, X86_REG_RBP },
  { ZYDIS_REGISTER_RSI, X86_REG_RSI },
  { ZYDIS_REGISTER_RDI, X86_REG_RDI },
  { ZYDIS_REGISTER_R8, X86_REG_R8 },
  { ZYDIS_REGISTER_R9, X86_REG_R9 },
  { ZYDIS_REGISTER_R10, X86_REG_R10 },
  { ZYDIS_REGISTER_R11, X86_REG_R11 },
  { ZYDIS_REGISTER_R12, X86_REG_R12 },
  { ZYDIS_REGISTER_R13, X86_REG_R13 },
  { ZYDIS_REGISTER_R14, X86_REG_R14 },
  { ZYDIS_REGISTER_R15, X86_REG_R15 },
  { ZYDIS_REGISTER_EFLAGS, X86_REG_EFLAGS },
  // Capstone doesnt have rflags? I guess it makes sense since there are only 20 something used flag bits
  { ZYDIS_REGISTER_RFLAGS, X86_REG_EFLAGS },
  { ZYDIS_REGISTER_IP, X86_REG_IP },
  { ZYDIS_REGISTER_EIP, X86_REG_EIP },
  { ZYDIS_REGISTER_RIP, X86_REG_RIP },
  { ZYDIS_REGISTER_XMM0, X86_REG_XMM0 },
  { ZYDIS_REGISTER_XMM1, X86_REG_XMM1 },
  { ZYDIS_REGISTER_XMM2, X86_REG_XMM2 },
  { ZYDIS_REGISTER_XMM3, X86_REG_XMM3 },
  { ZYDIS_REGISTER_XMM4, X86_REG_XMM4 },
  { ZYDIS_REGISTER_XMM5, X86_REG_XMM5 },
  { ZYDIS_REGISTER_XMM6, X86_REG_XMM6 },
  { ZYDIS_REGISTER_XMM7, X86_REG_XMM7 },
  { ZYDIS_REGISTER_XMM8, X86_REG_XMM8 },
  { ZYDIS_REGISTER_XMM9, X86_REG_XMM9 },
  { ZYDIS_REGISTER_XMM10, X86_REG_XMM10 },
  { ZYDIS_REGISTER_XMM11, X86_REG_XMM11 },
  { ZYDIS_REGISTER_XMM12, X86_REG_XMM12 },
  { ZYDIS_REGISTER_XMM13, X86_REG_XMM13 },
  { ZYDIS_REGISTER_XMM14, X86_REG_XMM14 },
  { ZYDIS_REGISTER_XMM15, X86_REG_XMM15 },
  { ZYDIS_REGISTER_XMM16, X86_REG_XMM16 },
  { ZYDIS_REGISTER_XMM17, X86_REG_XMM17 },
  { ZYDIS_REGISTER_XMM18, X86_REG_XMM18 },
  { ZYDIS_REGISTER_XMM19, X86_REG_XMM19 },
  { ZYDIS_REGISTER_XMM20, X86_REG_XMM20 },
  { ZYDIS_REGISTER_XMM21, X86_REG_XMM21 },
  { ZYDIS_REGISTER_XMM22, X86_REG_XMM22 },
  { ZYDIS_REGISTER_XMM23, X86_REG_XMM23 },
  { ZYDIS_REGISTER_XMM24, X86_REG_XMM24 },
  { ZYDIS_REGISTER_XMM25, X86_REG_XMM25 },
  { ZYDIS_REGISTER_XMM26, X86_REG_XMM26 },
  { ZYDIS_REGISTER_XMM27, X86_REG_XMM27 },
  { ZYDIS_REGISTER_XMM28, X86_REG_XMM28 },
  { ZYDIS_REGISTER_XMM29, X86_REG_XMM29 },
  { ZYDIS_REGISTER_XMM30, X86_REG_XMM30 },
  { ZYDIS_REGISTER_XMM31, X86_REG_XMM31 },
  { ZYDIS_REGISTER_YMM0, X86_REG_YMM0 },
  { ZYDIS_REGISTER_YMM1, X86_REG_YMM1 },
  { ZYDIS_REGISTER_YMM2, X86_REG_YMM2 },
  { ZYDIS_REGISTER_YMM3, X86_REG_YMM3 },
  { ZYDIS_REGISTER_YMM4, X86_REG_YMM4 },
  { ZYDIS_REGISTER_YMM5, X86_REG_YMM5 },
  { ZYDIS_REGISTER_YMM6, X86_REG_YMM6 },
  { ZYDIS_REGISTER_YMM7, X86_REG_YMM7 },
  { ZYDIS_REGISTER_YMM8, X86_REG_YMM8 },
  { ZYDIS_REGISTER_YMM9, X86_REG_YMM9 },
  { ZYDIS_REGISTER_YMM10, X86_REG_YMM10 },
  { ZYDIS_REGISTER_YMM11, X86_REG_YMM11 },
  { ZYDIS_REGISTER_YMM12, X86_REG_YMM12 },
  { ZYDIS_REGISTER_YMM13, X86_REG_YMM13 },
  { ZYDIS_REGISTER_YMM14, X86_REG_YMM14 },
  { ZYDIS_REGISTER_YMM15, X86_REG_YMM15 },
  { ZYDIS_REGISTER_YMM16, X86_REG_YMM16 },
  { ZYDIS_REGISTER_YMM17, X86_REG_YMM17 },
  { ZYDIS_REGISTER_YMM18, X86_REG_YMM18 },
  { ZYDIS_REGISTER_YMM19, X86_REG_YMM19 },
  { ZYDIS_REGISTER_YMM20, X86_REG_YMM20 },
  { ZYDIS_REGISTER_YMM21, X86_REG_YMM21 },
  { ZYDIS_REGISTER_YMM22, X86_REG_YMM22 },
  { ZYDIS_REGISTER_YMM23, X86_REG_YMM23 },
  { ZYDIS_REGISTER_YMM24, X86_REG_YMM24 },
  { ZYDIS_REGISTER_YMM25, X86_REG_YMM25 },
  { ZYDIS_REGISTER_YMM26, X86_REG_YMM26 },
  { ZYDIS_REGISTER_YMM27, X86_REG_YMM27 },
  { ZYDIS_REGISTER_YMM28, X86_REG_YMM28 },
  { ZYDIS_REGISTER_YMM29, X86_REG_YMM29 },
  { ZYDIS_REGISTER_YMM30, X86_REG_YMM30 },
  { ZYDIS_REGISTER_YMM31, X86_REG_YMM31 },
  { ZYDIS_REGISTER_ZMM0, X86_REG_ZMM0 },
  { ZYDIS_REGISTER_ZMM1, X86_REG_ZMM1 },
  { ZYDIS_REGISTER_ZMM2, X86_REG_ZMM2 },
  { ZYDIS_REGISTER_ZMM3, X86_REG_ZMM3 },
  { ZYDIS_REGISTER_ZMM4, X86_REG_ZMM4 },
  { ZYDIS_REGISTER_ZMM5, X86_REG_ZMM5 },
  { ZYDIS_REGISTER_ZMM6, X86_REG_ZMM6 },
  { ZYDIS_REGISTER_ZMM7, X86_REG_ZMM7 },
  { ZYDIS_REGISTER_ZMM8, X86_REG_ZMM8 },
  { ZYDIS_REGISTER_ZMM9, X86_REG_ZMM9 },
  { ZYDIS_REGISTER_ZMM10, X86_REG_ZMM10 },
  { ZYDIS_REGISTER_ZMM11, X86_REG_ZMM11 },
  { ZYDIS_REGISTER_ZMM12, X86_REG_ZMM12 },
  { ZYDIS_REGISTER_ZMM13, X86_REG_ZMM13 },
  { ZYDIS_REGISTER_ZMM14, X86_REG_ZMM14 },
  { ZYDIS_REGISTER_ZMM15, X86_REG_ZMM15 },
  { ZYDIS_REGISTER_ZMM16, X86_REG_ZMM16 },
  { ZYDIS_REGISTER_ZMM17, X86_REG_ZMM17 },
  { ZYDIS_REGISTER_ZMM18, X86_REG_ZMM18 },
  { ZYDIS_REGISTER_ZMM19, X86_REG_ZMM19 },
  { ZYDIS_REGISTER_ZMM20, X86_REG_ZMM20 },
  { ZYDIS_REGISTER_ZMM21, X86_REG_ZMM21 },
  { ZYDIS_REGISTER_ZMM22, X86_REG_ZMM22 },
  { ZYDIS_REGISTER_ZMM23, X86_REG_ZMM23 },
  { ZYDIS_REGISTER_ZMM24, X86_REG_ZMM24 },
  { ZYDIS_REGISTER_ZMM25, X86_REG_ZMM25 },
  { ZYDIS_REGISTER_ZMM26, X86_REG_ZMM26 },
  { ZYDIS_REGISTER_ZMM27, X86_REG_ZMM27 },
  { ZYDIS_REGISTER_ZMM28, X86_REG_ZMM28 },
  { ZYDIS_REGISTER_ZMM29, X86_REG_ZMM29 },
  { ZYDIS_REGISTER_ZMM30, X86_REG_ZMM30 },
  { ZYDIS_REGISTER_ZMM31, X86_REG_ZMM31 },
  { ZYDIS_REGISTER_CR0, X86_REG_CR0 },
  { ZYDIS_REGISTER_CR1, X86_REG_CR1 },
  { ZYDIS_REGISTER_CR2, X86_REG_CR2 },
  { ZYDIS_REGISTER_CR3, X86_REG_CR3 },
  { ZYDIS_REGISTER_CR4, X86_REG_CR4 },
  { ZYDIS_REGISTER_CR5, X86_REG_CR5 },
  { ZYDIS_REGISTER_CR6, X86_REG_CR6 },
  { ZYDIS_REGISTER_CR7, X86_REG_CR7 },
  { ZYDIS_REGISTER_CR8, X86_REG_CR8 },
  { ZYDIS_REGISTER_CR9, X86_REG_CR9 },
  { ZYDIS_REGISTER_CR10, X86_REG_CR10 },
  { ZYDIS_REGISTER_CR11, X86_REG_CR11 },
  { ZYDIS_REGISTER_CR12, X86_REG_CR12 },
  { ZYDIS_REGISTER_CR13, X86_REG_CR13 },
  { ZYDIS_REGISTER_CR14, X86_REG_CR14 },
  { ZYDIS_REGISTER_CR15, X86_REG_CR15 },
  { ZYDIS_REGISTER_MM0, X86_REG_MM0 },
  { ZYDIS_REGISTER_MM1, X86_REG_MM1 },
  { ZYDIS_REGISTER_MM2, X86_REG_MM2 },
  { ZYDIS_REGISTER_MM3, X86_REG_MM3 },
  { ZYDIS_REGISTER_MM4, X86_REG_MM4 },
  { ZYDIS_REGISTER_MM5, X86_REG_MM5 },
  { ZYDIS_REGISTER_MM6, X86_REG_MM6 },
  { ZYDIS_REGISTER_MM7, X86_REG_MM7 },
  { ZYDIS_REGISTER_DR0, X86_REG_DR0 },
  { ZYDIS_REGISTER_DR1, X86_REG_DR1 },
  { ZYDIS_REGISTER_DR2, X86_REG_DR2 },
  { ZYDIS_REGISTER_DR3, X86_REG_DR3 },
  { ZYDIS_REGISTER_DR4, X86_REG_DR4 },
  { ZYDIS_REGISTER_DR5, X86_REG_DR5 },
  { ZYDIS_REGISTER_DR6, X86_REG_DR6 },
  { ZYDIS_REGISTER_DR7, X86_REG_DR7 },
  { ZYDIS_REGISTER_DR8, X86_REG_DR8 },
  { ZYDIS_REGISTER_DR9, X86_REG_DR9 },
  { ZYDIS_REGISTER_DR10, X86_REG_DR10 },
  { ZYDIS_REGISTER_DR11, X86_REG_DR11 },
  { ZYDIS_REGISTER_DR12, X86_REG_DR12 },
  { ZYDIS_REGISTER_DR13, X86_REG_DR13 },
  { ZYDIS_REGISTER_DR14, X86_REG_DR14 },
  { ZYDIS_REGISTER_DR15, X86_REG_DR15 }
};

//Implement a way to get size from register in a constexpr way
constexpr x86_reg zyreg_to_capreg(ZydisRegister reg)
{
  auto* val = std::find(std::begin(zyreg_to_capreg_arr), std::end(zyreg_to_capreg_arr), reg);
  if (val) return val->second;
  else return X86_REG_INVALID;
}

namespace vtil {
  template<>
  struct register_cast<ZydisRegister>
  {
    constexpr register_desc operator()(ZydisRegister zyreg)
    {
      //Why not use the work that was already done
      register_cast<x86_reg> cast;
      return cast(zyreg_to_capreg(zyreg));
    }
  };
}