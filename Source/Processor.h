#pragma once
#include "Types.h"
#include <array>
#include <bitset>

class Processor {
public:
    void execute();

    u8 take_byte();
    u8& get_byte(u16 address);

    void do_adc(u8 value);
    void do_sbc(u8 value);
    void do_ora(u8 value);
    void do_and(u8 value);
    void do_eor(u8 value);
    void do_bit(u8 value);
    void do_asl(u8& value);
    void do_lsr(u8& value);
    void do_rol(u8& value);
    void do_ror(u8& value);
    void do_lda(u8 value);
    void do_ldx(u8 value);
    void do_ldy(u8 value);
    void do_cmp(u8 value);
    void do_cpx(u8 value);
    void do_cpy(u8 value);
    void do_inc(u8& value);
    void do_dec(u8& value);

    // Address modes
    u8& abs();
    u8& abs_x();
    u8& abs_y();
    u8& ind();
    u8& x_ind();
    u8& ind_y();
    u8& zpg();
    u8& zpg_x();
    u8& zpg_y();

    [[nodiscard]] inline bool get_negative() const { return m_sr[7]; }
    [[nodiscard]] inline bool get_overflow() const { return m_sr[6]; }
    [[nodiscard]] inline bool get_ignored() const { return m_sr[5]; }
    [[nodiscard]] inline bool get_break() const { return m_sr[4]; }
    [[nodiscard]] inline bool get_decimal() const { return m_sr[3]; }
    [[nodiscard]] inline bool get_interrupt() const { return m_sr[2]; }
    [[nodiscard]] inline bool get_zero() const { return m_sr[1]; }
    [[nodiscard]] inline bool get_carry() const { return m_sr[0]; }

    inline void set_negative(bool v) { m_sr[7] = v; }
    inline void set_overflow(bool v) { m_sr[6] = v; }
    inline void set_ignored(bool v) { m_sr[5] = v; }
    inline void set_break(bool v) { m_sr[4] = v; }
    inline void set_decimal(bool v) { m_sr[3] = v; }
    inline void set_interrupt(bool v) { m_sr[2] = v; }
    inline void set_zero(bool v) { m_sr[1] = v; }
    inline void set_carry(bool v) { m_sr[0] = v; }

    void push_stack(u16);
    void push_stack(u8);
    void push_stack(std::bitset<8>);
    u8& pop_stack();

private:
    u16 m_pc { 0 };
    u8 m_ac { 0 };
    u8 m_x { 0 };
    u8 m_y { 0 };
    std::bitset<8> m_sr { 0b00110100 };
    u8 m_sp { 0 };

    // TODO: this is probably mapper dependent
    std::array<u8, 2048> m_ram {};
};
