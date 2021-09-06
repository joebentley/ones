#include "Processor.h"
#include <fmt/core.h>

inline bool get_bit(u8 value, u8 bit)
{
    return (value & (1 << bit)) > 0;
}

inline bool turn_bit_on(u8 value, u8 bit)
{
    return value | (1 << bit);
}

inline bool check_msb(u8 value)
{
    return get_bit(value, 7);
}

inline bool check_lsb(u8 value)
{
    return get_bit(value, 0);
}

void Processor::execute()
{
    switch (take_byte()) {
    case 0x00: { // BRK impl
        push_stack(static_cast<u16>(m_pc + 1));
        set_break(true);
        push_stack(m_sr);
        break;
    }
    case 0x01: { // ORA X,ind
        do_ora(x_ind());
        break;
    }
    case 0x05: { // ORA zpg
        do_ora(zpg());
        break;
    }
    case 0x06: { // ASL zpg
        do_asl(zpg());
        break;
    }
    case 0x08: { // PHP impl
        set_ignored(true);
        push_stack(m_sp);
        break;
    }
    case 0x09: { // ORA #
        do_ora(take_byte());
        break;
    }
    case 0x0A: { // ASL A
        do_asl(m_ac);
        break;
    }
    case 0x0D: { // ORA abs
        do_ora(abs());
        break;
    }
    case 0x0E: { // ASL abs
        do_asl(abs());
        break;
    }
    case 0x10: { // BPL rel
        auto rel = take_byte();
        if (!get_negative())
            m_pc = m_pc - 1 + rel;
        break;
    }
    case 0x11: { // ORA ind,Y
        do_ora(ind_y());
        break;
    }
    case 0x15: { // ORA zpg,X
        do_ora(zpg_x());
        break;
    }
    case 0x16: { // ASL zpg,X
        do_asl(zpg_x());
        break;
    }
    case 0x18: { // CLC impl
        set_carry(false);
        break;
    }
    case 0x19: { // ORA abs,Y
        do_ora(abs_y());
        break;
    }
    case 0x1D: { // ORA abs,X
        do_ora(abs_x());
        break;
    }
    case 0x1E: { // ASL abs,X
        do_asl(abs_x());
        break;
    }
    case 0x20: { // JSR abs
        // TODO: check what we're pushing to stack here, it might be wrong
        push_stack(static_cast<u16>(m_pc + 2));
        m_pc = take_byte() + (take_byte() << 8);
        break;
    }
    case 0x21: { // AND X,ind
        do_and(x_ind());
        break;
    }
    case 0x24: { // BIT zpg
        do_bit(zpg());
        break;
    }
    case 0x25: { // AND zpg
        do_and(zpg());
        break;
    }
    case 0x26: { // ROL zpg
        do_rol(zpg());
        break;
    }
    case 0x28: { // PLP impl
        auto byte = pop_stack();
        // TODO: maybe could be done better
        for (int i = 0; i < 8; i++) {
            if (i == 5 || i == 4)
                continue;
            m_sr.set(i, get_bit(byte, i));
        }
        break;
    }
    case 0x29: { // AND #
        do_and(take_byte());
        break;
    }
    case 0x2A: { // ROL A
        do_rol(m_ac);
        break;
    }
    case 0x2C: { // BIT abs
        do_bit(abs());
        break;
    }
    case 0x2D: { // AND abs
        do_and(abs());
        break;
    }
    case 0x2E: { // ROL abs
        do_rol(abs());
        break;
    }
    case 0x30: { // BMI rel
        auto rel = take_byte();
        if (get_negative())
            m_pc = m_pc - 1 + rel;
        break;
    }
    case 0x31: { // AND ind,Y
        do_and(ind_y());
        break;
    }
    case 0x35: { // AND zpg,X
        do_and(zpg_x());
        break;
    }
    case 0x36: { // ROL zpg,X
        do_rol(zpg_x());
        break;
    }
    case 0x38: { // SEC impl
        set_carry(true);
        break;
    }
    case 0x39: { // AND abs,Y
        do_and(abs_y());
        break;
    }
    case 0x3D: { // AND abs,X
        do_and(abs_x());
        break;
    }
    case 0x3E: { // ROL abs,X
        do_rol(abs_x());
        break;
    }
    case 0x40: { // RTI impl
        auto byte = pop_stack();
        // TODO: maybe could be done better (see above)
        for (int i = 0; i < 8; i++) {
            if (i == 5 || i == 4)
                continue;
            m_sr.set(i, get_bit(byte, i));
        }
        // TODO: check this
        m_pc = (pop_stack() << 8) + pop_stack();
        break;
    }
    case 0x41: { // EOR X,ind
        do_eor(x_ind());
        break;
    }
    case 0x45: { // EOR zpg
        do_eor(zpg());
        break;
    }
    case 0x46: { // LSR zpg
        do_lsr(zpg());
        break;
    }
    case 0x48: { // PHA impl
        push_stack(m_ac);
        break;
    }
    case 0x49: { // EOR #
        do_eor(take_byte());
        break;
    }
    case 0x4A: { // LSR A
        do_lsr(m_ac);
        break;
    }
    case 0x4C: { // JMP abs
        m_pc = take_byte() + (take_byte() << 8);
        break;
    }
    case 0x4D: { // EOR abs
        do_eor(abs());
        break;
    }
    case 0x4E: { // LSR abs
        do_lsr(abs());
        break;
    }
    case 0x50: { // BVC rel
        auto rel = take_byte();
        if (!get_overflow())
            m_pc = m_pc - 1 + rel;
        break;
    }
    case 0x51: { // EOR ind,Y
        do_eor(ind_y());
        break;
    }
    case 0x55: { // EOR zpg,X
        do_eor(zpg_x());
        break;
    }
    case 0x56: { // LSR zpg,X
        do_lsr(zpg_x());
        break;
    }
    case 0x58: { // CLI impl
        set_interrupt(false);
        break;
    }
    case 0x59: { // EOR abs,Y
        do_eor(abs_y());
        break;
    }
    case 0x5D: { // EOR abs,X
        do_eor(abs_x());
        break;
    }
    case 0x5E: { // LSR abs
        do_lsr(abs());
        break;
    }
    case 0x60: { // RTS impl
        // TODO: check this
        m_pc = pop_stack() + (pop_stack() << 8);
        break;
    }
    case 0x61: { // ADC X,ind
        do_adc(x_ind());
        break;
    }
    case 0x65: { // ADC zpg
        do_adc(zpg());
        break;
    }
    case 0x66: { // ROR zpg
        do_ror(zpg());
        break;
    }
    case 0x68: { // PLA impl
        m_ac = pop_stack();
        break;
    }
    case 0x69: { // ADC #
        do_adc(take_byte());
        break;
    }
    case 0x6A: { // ROR A
        do_ror(m_ac);
        break;
    }
    case 0x6C: { // JMP ind
        m_pc = ind(); // TODO: quite unsure about this
        break;
    }
    case 0x6D: { // ADC abs
        do_adc(abs());
        break;
    }
    case 0x6E: { // ROR abs
        do_ror(abs());
        break;
    }
    case 0x70: { // BVS rel
        auto rel = take_byte();
        if (get_overflow())
            m_pc = m_pc - 1 + rel;
        break;
    }
    case 0x71: { // ADC ind,Y
        do_adc(ind_y());
        break;
    }
    case 0x75: { // ADC zpg,X
        do_adc(zpg_x());
        break;
    }
    case 0x76: { // ROR zpg,X
        do_ror(zpg_x());
        break;
    }
    case 0x78: { // SEI impl
        set_interrupt(false);
        break;
    }
    case 0x79: { // ADC abs,Y
        do_adc(abs_y());
        break;
    }
    case 0x7D: { // ADC abs,X
        do_adc(abs_x());
        break;
    }
    case 0x7E: { // ROR abs,X
        do_ror(abs_x());
        break;
    }
    case 0x81: { // STA X,ind
        x_ind() = m_ac;
        break;
    }
    case 0x84: { // STY zpg
        zpg() = m_y;
        break;
    }
    case 0x85: { // STA zpg
        zpg() = m_ac;
        break;
    }
    case 0x86: { // STX zpg
        zpg() = m_x;
        break;
    }
    case 0x88: { // DEY impl
        m_y -= 1;
        set_negative(check_msb(m_y));
        set_zero(m_y == 0);
        break;
    }
    case 0x8A: { // TXA impl
        m_ac = m_x;
        set_negative(check_msb(m_ac));
        set_zero(m_ac == 0);
        break;
    }
    case 0x8C: { // STY abs
        abs() = m_y;
        break;
    }
    case 0x8D: { // STA abs
        abs() = m_ac;
        break;
    }
    case 0x8E: { // STX abs
        abs() = m_x;
        break;
    }
    case 0x90: { // BCC rel
        auto rel = take_byte();
        if (!get_carry())
            m_pc = m_pc - 1 + rel;
        break;
    }
    case 0x91: { // STA ind,Y
        ind_y() = m_ac;
        break;
    }
    case 0x94: { // STY zpg,X
        zpg_x() = m_y;
        break;
    }
    case 0x95: { // STA zpg,X
        zpg_x() = m_ac;
        break;
    }
    case 0x96: { // STX zpg,Y
        zpg_y() = m_x;
        break;
    }
    case 0x98: { // TYA impl
        m_ac = m_y;
        set_negative(check_msb(m_ac));
        set_zero(m_ac == 0);
        break;
    }
    case 0x99: { // STA abs,Y
        abs_y() = m_ac;
        break;
    }
    case 0x9A: { // TXS impl
        m_sp = m_x;
        break;
    }
    case 0x9D: { // STA abs,X
        abs_x() = m_ac;
        break;
    }
    case 0xA0: { // LDY #
        do_ldy(take_byte());
        break;
    }
    case 0xA1: { // LDA X,ind
        do_lda(x_ind());
        break;
    }
    case 0xA2: { // LDX #
        do_ldx(take_byte());
        break;
    }
    case 0xA4: { // LDY zpg
        do_ldy(zpg());
        break;
    }
    case 0xA5: { // LDA zpg
        do_lda(zpg());
        break;
    }
    case 0xA6: { // LDX zpg
        do_ldx(zpg());
        break;
    }
    case 0xA8: { // TAY impl
        m_y = m_ac;
        set_negative(check_msb(m_y));
        set_zero(m_y == 0);
        break;
    }
    case 0xA9: { // LDA #
        do_lda(take_byte());
        break;
    }
    case 0xAA: { // TAX impl
        m_x = m_ac;
        set_negative(check_msb(m_x));
        set_zero(m_x == 0);
        break;
    }
    case 0xAC: { // LDY abs
        do_ldy(abs());
        break;
    }
    case 0xAD: { // LDA abs
        do_lda(abs());
        break;
    }
    case 0xAE: { // LDX abs
        do_ldx(abs());
        break;
    }
    case 0xB0: { // BCS rel
        auto rel = take_byte();
        if (get_carry())
            m_pc = m_pc - 1 + rel;
        break;
    }
    case 0xB1: { // LDA ind,Y
        do_lda(ind_y());
        break;
    }
    case 0xB4: { // LDY zpg,X
        do_ldy(zpg_x());
        break;
    }
    case 0xB5: { // LDA zpg,X
        do_lda(zpg_x());
        break;
    }
    case 0xB6: { // LDX zpg,Y
        do_ldx(zpg_y());
        break;
    }
    case 0xB8: { // CLV impl
        set_overflow(false);
        break;
    }
    case 0xB9: { // LDA abs,Y
        do_lda(abs_y());
        break;
    }
    case 0xBA: { // TSX impl
        m_x = m_sp;
        set_negative(check_msb(m_x));
        set_zero(m_x == 0);
        break;
    }
    case 0xBC: { // LDY abs,X
        do_ldy(abs_x());
        break;
    }
    case 0xBD: { // LDA abs,X
        do_lda(abs_x());
        break;
    }
    case 0xBE: { // LDX abs,Y
        do_ldx(abs_y());
        break;
    }
    case 0xC0: { // CPY #
        do_cpy(take_byte());
        break;
    }
    case 0xC1: { // CMP X,ind
        do_cpx(x_ind());
        break;
    }
    case 0xC4: { // CPY zpg
        do_cpy(zpg());
        break;
    }
    case 0xC5: { // CMP zpg
        do_cmp(zpg());
        break;
    }
    case 0xC6: { // DEC zpg
        do_dec(zpg());
        break;
    }
    case 0xC8: { // INY impl
        m_y += 1;
        set_negative(check_msb(m_y));
        set_zero(m_y == 0);
        break;
    }
    case 0xC9: { // CMP #
        do_cmp(take_byte());
        break;
    }
    case 0xCA: { // DEX impl
        m_x -= 1;
        set_negative(check_msb(m_x));
        set_zero(m_x == 0);
        break;
    }
    case 0xCC: { // CPY abs
        do_cpy(abs());
        break;
    }
    case 0xCD: { // CMP abs
        do_cmp(abs());
        break;
    }
    case 0xCE: { // DEC abs
        do_dec(abs());
        break;
    }
    case 0xD0: { // BNE rel
        auto rel = take_byte();
        if (!get_zero())
            m_pc = m_pc - 1 + rel;
        break;
    }
    case 0xD1: { // CMP ind,Y
        do_cmp(ind_y());
        break;
    }
    case 0xD5: { // CMP zpg,X
        do_cmp(zpg_x());
        break;
    }
    case 0xD6: { // DEC zpg,X
        do_dec(zpg_x());
        break;
    }
    case 0xD8: { // CLD impl
        set_decimal(false);
        break;
    }
    case 0xD9: { // CMP abs,Y
        do_cmp(abs_y());
        break;
    }
    case 0xDD: { // CMP abs,X
        do_cmp(abs_x());
        break;
    }
    case 0xDE: { // DEC abs,X
        do_dec(abs_x());
        break;
    }
    case 0xE0: { // CPX #
        do_cpx(take_byte());
        break;
    }
    case 0xE1: { // SBC X,ind
        do_sbc(x_ind());
        break;
    }
    case 0xE4: { // CPX zpg
        do_cpx(zpg());
        break;
    }
    case 0xE5: { // SBC zpg
        do_sbc(zpg());
        break;
    }
    case 0xE6: { // INC zpg
        do_inc(zpg());
        break;
    }
    case 0xE8: { // INX impl
        m_x += 1;
        set_negative(check_msb(m_x));
        set_zero(m_x == 0);
        break;
    }
    case 0xE9: { // SBC #
        do_sbc(take_byte());
        break;
    }
    case 0xEA: { // NOP impl
        break;
    }
    case 0xEC: { // CPX abs
        do_cpx(abs());
        break;
    }
    case 0xED: { // SBC abs
        do_sbc(abs());
        break;
    }
    case 0xEE: { // INC abs
        do_inc(abs());
        break;
    }
    case 0xF0: { // BEQ rel
        auto rel = take_byte();
        if (get_zero())
            m_pc = m_pc - 1 + rel;
        break;
    }
    case 0xF1: { // SBC ind,Y
        do_sbc(ind_y());
        break;
    }
    case 0xF5: { // SBC zpg,X
        do_sbc(zpg_x());
        break;
    }
    case 0xF6: { // INC zpg,X
        do_inc(zpg_x());
        break;
    }
    case 0xF8: { // SED impl
        set_decimal(true);
        break;
    }
    case 0xF9: { // SBC abs,Y
        do_sbc(abs_y());
        break;
    }
    case 0xFD: { // SBC abs,X
        do_sbc(abs_x());
        break;
    }
    case 0xFE: { // INC abs,X
        do_inc(abs_x());
        break;
    }
    default:
        fmt::print("Unrecognised opcode: {}", get_byte(m_pc - 1));
        return;
    }
}

// TODO: decimal is not implemented
void Processor::do_adc(u8 value)
{
    auto has_carry = check_msb(m_ac);

    // TODO: cleanup overflow code
    auto is_acc_ngv = check_msb(m_ac);
    auto is_operand_ngv = check_msb(value);
    auto is_result_ngv = check_msb(m_ac + value);
    set_overflow((is_acc_ngv && is_operand_ngv && !is_result_ngv) || (!is_acc_ngv && !is_operand_ngv && is_result_ngv));

    m_ac += value + (get_carry() ? 0 : 1);
    set_carry(has_carry);
    set_zero(m_ac == 0);
    set_negative(check_msb(m_ac));
}

void Processor::do_sbc(u8 value)
{
    auto has_carry = check_msb(m_ac);

    // TODO: cleanup overflow code
    auto is_acc_ngv = check_msb(m_ac);
    auto is_operand_ngv = check_msb(value);
    auto is_result_ngv = check_msb(m_ac - value);
    set_overflow((is_acc_ngv && is_operand_ngv && !is_result_ngv) || (!is_acc_ngv && !is_operand_ngv && is_result_ngv));

    m_ac -= value + (get_carry() ? 0 : 1); // TODO: unsure about application of carry here
    set_carry(has_carry);
    set_zero(m_ac == 0);
    set_negative(check_msb(m_ac));
}

void Processor::do_ora(u8 value)
{
    m_ac |= value;
    set_negative(check_msb(m_ac));
    set_zero(m_ac == 0);
}

void Processor::do_and(u8 value)
{
    m_ac &= value;
    set_negative(check_msb(m_ac));
    set_zero(m_ac == 0);
}

void Processor::do_eor(u8 value)
{
    m_ac ^= value;
    set_negative(check_msb(m_ac));
    set_zero(m_ac == 0);
}

void Processor::do_bit(u8 value)
{
    set_negative(get_bit(value, 7));
    set_overflow(get_bit(value, 6));
    set_zero(value & m_ac);
}

void Processor::do_asl(u8& value)
{
    set_carry(check_msb(value));
    value <<= 1;
    set_negative(check_msb(value));
    set_zero(value == 0);
}

void Processor::do_lsr(u8& value)
{
    set_carry(check_lsb(value)); // TODO: is this correct?
    value >>= 1;
    set_negative(check_msb(value));
    set_zero(value == 0);
}

void Processor::do_rol(u8& value)
{
    auto had_carry = get_carry();
    set_carry(check_msb(value));
    value <<= 1;
    if (had_carry)
        turn_bit_on(value, 0); // set first bit
}

void Processor::do_ror(u8& value)
{
    auto had_carry = get_carry();
    set_carry(check_lsb(value));
    value >>= 1;
    if (had_carry)
        turn_bit_on(value, 7); // set highest bit
}

void Processor::do_lda(u8 value)
{
    m_ac = value;
    set_negative(check_msb(m_ac));
    set_zero(m_ac == 0);
}

void Processor::do_ldx(u8 value)
{
    m_x = value;
    set_negative(check_msb(m_x));
    set_zero(m_x == 0);
}

void Processor::do_ldy(u8 value)
{
    m_y = value;
    set_negative(check_msb(m_y));
    set_zero(m_y == 0);
}


void Processor::do_cmp(u8 value)
{
    u8 result = m_ac - value;
    set_negative(check_msb(result));
    set_zero(result == 0);
    set_carry(check_msb(result)); // TODO: unsure here
}

void Processor::do_cpx(u8 value)
{
    u8 result = m_x - value;
    set_negative(check_msb(result));
    set_zero(result == 0);
    set_carry(check_msb(result)); // TODO: same here
}

void Processor::do_cpy(u8 value)
{
    u8 result = m_y - value;
    set_negative(check_msb(result));
    set_zero(result == 0);
    set_carry(check_msb(result)); // TODO: same here
}

void Processor::do_inc(u8& value)
{
    value += 1;
    set_negative(check_msb(value));
    set_zero(value == 0);
}

void Processor::do_dec(u8& value)
{
    value -= 1;
    set_negative(check_msb(value));
    set_zero(value == 0);
}

u8 Processor::take_byte()
{
    return get_byte(m_pc++);
}

u8& Processor::get_byte(u16 address)
{
    // TODO: map the memory
    return m_ram[address];
}

u8& Processor::abs()
{
    auto arg = take_byte();
    auto arg2 = take_byte();
    return get_byte(arg + (arg2 << 8));
}

u8& Processor::abs_x()
{
    auto arg = take_byte();
    auto arg2 = take_byte();
    // TODO: with carry?
    return get_byte(arg + (arg2 << 8) + m_x);
}

u8& Processor::abs_y()
{
    auto arg = take_byte();
    auto arg2 = take_byte();
    // TODO: with carry?
    return get_byte(arg + (arg2 << 8) + m_y);
}

u8& Processor::ind()
{
    auto arg = take_byte();
    auto arg2 = take_byte();
    return get_byte(get_byte(arg + (arg2 << 8)));
}

u8& Processor::x_ind()
{
    auto arg = take_byte();
    return get_byte(get_byte(arg + m_x));
}

u8& Processor::ind_y()
{
    auto arg = take_byte();
    // TODO: with carry?
    return get_byte(get_byte(arg) + (get_byte(arg + 1) << 8) + m_y);
}

u8& Processor::zpg()
{
    auto arg = take_byte();
    return get_byte(arg);
}

u8& Processor::zpg_x()
{
    auto arg = take_byte();
    return get_byte(arg + m_x);
}

u8& Processor::zpg_y()
{
    auto arg = take_byte();
    return get_byte(arg + m_y);
}

void Processor::push_stack(u16 value)
{
    push_stack(static_cast<u8>(value & 0xFF));
    push_stack(static_cast<u8>(value & 0xFF00));
}

void Processor::push_stack(u8 value)
{
    get_byte(0x0100 + m_sp) = value;
    m_sp++;
}

void Processor::push_stack(std::bitset<8> value)
{
    push_stack(static_cast<u8>(value.to_ulong()));
}

u8& Processor::pop_stack()
{
    auto& value = get_byte(0x0100 + m_sp);
    m_sp--;
    return value;
}
