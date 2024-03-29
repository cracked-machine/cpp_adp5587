// MIT License

// Copyright (c) 2022 Chris Sutton

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef __ADP5587_COMMON_HPP__
#define __ADP5587_COMMON_HPP__

#include <i2c_utils_ref.hpp>
#include <isr_manager_stm32g0.hpp>
#include <restricted_base.hpp>

namespace adp5587
{

class CommonData
{
public:
  // @brief Incomplete list of ADP5587 device registers
  // see datasheet page 15 (https://www.analog.com/media/en/technical-documentation/data-sheets/adp5587.pdf)
  enum Registers
  {
    DEV_ID          = 0x00,
    CFG             = 0x01,
    INT_STAT        = 0x02,
    KEY_LCK_EC_STAT = 0x03,
    KEY_EVENTA      = 0x04,
    KEY_EVENTB      = 0x05,
    KEY_EVENTC      = 0x06,
    KEY_EVENTD      = 0x07,
    KEY_EVENTE      = 0x08,
    KEY_EVENTF      = 0x09,
    KEY_EVENTG      = 0x0A,
    KEY_EVENTH      = 0x0B,
    KEY_EVENTI      = 0x0C,
    KEY_EVENTJ      = 0x0D,
    GPIO_INT_STAT1  = 0x11,
    GPIO_INT_STAT2  = 0x12,
    GPIO_INT_STAT3  = 0x13,

    GPIO_INT_EN1  = 0x1A,
    GPIO_INT_EN2  = 0x1B,
    GPIO_INT_EN3  = 0x1C,
    KP_GPIO1      = 0x1D,
    KP_GPIO2      = 0x1E,
    KP_GPIO3      = 0x1F,
    GPI_EM_REG1   = 0x20,
    GPI_EM_REG2   = 0x21,
    GPI_EM_REG3   = 0x22,
    GPIO_DIR1     = 0x23,
    GPIO_DIR2     = 0x24,
    GPIO_DIR3     = 0x25,
    GPIO_INT_LVL1 = 0x26,
    GPIO_INT_LVL2 = 0x27,
    GPIO_INT_LVL3 = 0x28,
    DEBOUNCE_DIS1 = 0x29,
    DEBOUNCE_DIS2 = 0x30,
    DEBOUNCE_DIS3 = 0x31,
    GPIO_PULL1    = 0x32,
    GPIO_PULL2    = 0x33,
    GPIO_PULL3    = 0x34,

  };

  // @brief  Values for Keypad or GPIO selection registers
  enum KP_GPIO
  {
    // clang-format off
    R0 = 0b00000001,
    R1 = 0b00000010,
    R2 = 0b00000100,
    R3 = 0b00001000,
    R4 = 0b00010000,
    R5 = 0b00100000,
    R6 = 0b01000000,
    R7 = 0b10000000,

    C0 = 0b00000001,
    C1 = 0b00000010,
    C2 = 0b00000100,
    C3 = 0b00001000,
    C4 = 0b00010000,
    C5 = 0b00100000,
    C6 = 0b01000000,
    C7 = 0b10000000,
    C8 = 0b00000001,
    C9 = 0b00000010,
    // clang-format on
  };

  // Keypad release encodings. These values appear in the KeyEventReg entries after key press/release events
  // see datasheet page 9 (https://www.analog.com/media/en/technical-documentation/data-sheets/adp5587.pdf)
  // To get Key press events IDs, bitwise-OR the KeyEventIndex::XX_OFF values with KeyEventIndex::ON .
  // See the templated overload operator function below.
  enum class KeyEventIndex
  {
    // clang-format off
    INIT=0,
    // these default to key release events
    A7_OFF=71,	A6_OFF=61,	A5_OFF=51,	A4_OFF=41,	A3_OFF=31,	A2_OFF=21,	A1_OFF=11,	A0_OFF=1,
    B7_OFF=72,	B6_OFF=62,	B5_OFF=52,	B4_OFF=42,	B3_OFF=32,	B2_OFF=22,	B1_OFF=12,	B0_OFF=2,
    C7_OFF=73,	C6_OFF=63,	C5_OFF=53,	C4_OFF=43,	C3_OFF=33,	C2_OFF=23,	C1_OFF=13,	C0_OFF=3,
    D7_OFF=74,	D6_OFF=64,	D5_OFF=54,	D4_OFF=44,	D3_OFF=34,	D2_OFF=24,	D1_OFF=14,	D0_OFF=4,
    E7_OFF=75,	E6_OFF=65,	E5_OFF=55,	E4_OFF=45,	E3_OFF=35,	E2_OFF=25,	E1_OFF=15,	E0_OFF=5,
    F7_OFF=76,	F6_OFF=66,	F5_OFF=56,	F4_OFF=46,	F3_OFF=36,	F2_OFF=26,	F1_OFF=16,	F0_OFF=6,
    G7_OFF=77,	G6_OFF=67,	G5_OFF=57,	G4_OFF=47,	G3_OFF=37,	G2_OFF=27,	G1_OFF=17,	G0_OFF=7,
    H7_OFF=78,	H6_OFF=68,	H5_OFF=58,	H4_OFF=48,	H3_OFF=38,	H2_OFF=28,	H1_OFF=18,	H0_OFF=8,
    I7_OFF=79,	I6_OFF=69,	I5_OFF=59,	I4_OFF=49,	I3_OFF=39,	I2_OFF=29,	I1_OFF=19,	I0_OFF=9,
    J7_OFF=80,	J6_OFF=70,	J5_OFF=60,	J4_OFF=50,	J3_OFF=40,	J2_OFF=30,	J1_OFF=20,	J0_OFF=10, 
    // this bit will be set if the key was pressed
    ON=128,
    // clang-format on
  };

  enum class GPIKeyMappings
  {

    // these default to key release events
    R0 = 97,
    R1 = 98,
    R2 = 99,
    R3 = 100,
    R4 = 101,
    R5 = 102,
    R6 = 103,
    R7 = 104,
    C0 = 105,
    C1 = 106,
    C2 = 107,
    C3 = 108,
    C4 = 109,
    C5 = 110,
    C6 = 111,
    C7 = 112,
    C8 = 113,
    C9 = 114,
    // this bit will be set if the key was pressed
    ON = 128,

  };

  // @brief Bitwise-OR two scoped enum literals together
  // @tparam SCOPED_ENUM The scoped enum type.
  // @param L The left literal operand
  // @param R The right literal operand
  // @return constexpr SCOPED_ENUM Returns the combined value as SCOPED_ENUM enum type
  template <typename SCOPED_ENUM>
  constexpr friend SCOPED_ENUM operator|(SCOPED_ENUM L, SCOPED_ENUM R)
  {
    return static_cast<SCOPED_ENUM>(static_cast<int>(L) | static_cast<int>(R));
  }

  // Interrupt status register
  enum IntStatusReg
  {
    KE_INT       = (1 << 0), // Key events interrupt status. When set, write 1 to clear.
    GPI_INT      = (1 << 1), // GPI interrupt status. When set, write 1 to clear.
    K_LCK_INT    = (1 << 2), // Keylock interrupt status. When set, write 1 to clear.
    OVR_FLOW_INT = (1 << 3), // Overflow interrupt status. When set, write 1 to clear.
  };

  // Keylock and event counter register
  enum KeyLckEvCntReg
  {
    KEC1     = (1 << 0), // 3-bit key event count of key event register.
    KEC2     = (1 << 1),
    KEC3     = (1 << 2),
    KEC4     = (1 << 3),
    LCK1     = (1 << 4), // 2-bit keypad lock status[1:0] (00 = unlocked; 11 = locked; read-only bits).
    LCK2     = (1 << 5),
    K_LCK_EN = (1 << 6), // 0: lock feature is disabled. 1: lock feature is enabled.
  };

  // @brief Configuration Register 1
  enum ConfigReg
  {
    KE_IEN       = (1 << 0), // Key events interrupt enable.
    GPI_IEN      = (1 << 1), // GPI interrupt enable.
    K_LCK_IM     = (1 << 2), // Keypad lock interrupt mask.
    OVR_FLOW_IEN = (1 << 3), // Overflow interrupt enable.
    INT_CFG      = (1 << 4), // Interrupt configuration.
    OVR_FLOW_M   = (1 << 5), // Overflow mode.
    GPIEM_CFG    = (1 << 6), // GPI event mode configuration.
    AUTO_INC     = (1 << 7), // 2C auto-increment. Burst read is supported; burst write is not supported.
  };

protected:
  // @brief local store for ADP5587 key event FIFO
  std::array<KeyEventIndex, 10> m_key_event_fifo{KeyEventIndex::INIT};

  // @brief The i2c slave address for ADP5587ACPZ-1-R7
  const uint8_t m_i2c_addr{0x60};

private:





};

// out-of-class declaration for friend operator overloading
template <typename SCOPED_ENUM>
constexpr SCOPED_ENUM operator|(SCOPED_ENUM L, SCOPED_ENUM R);

} // namespace adp5587

#endif // __ADP5587_COMMON_HPP__