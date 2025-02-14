export enum COMMAND_TYPE {
    NONE           = 0b00000000,
    COMMAND_PON    = 0b00000001, // 碰
    COMMAND_GON    = 0b00000010, // 直槓
    COMMAND_ONGON  = 0b00000100, // 暗槓
    COMMAND_PONGON = 0b00001000, // 面下槓
    COMMAND_HU     = 0b00010000, // 胡
    COMMAND_ZIMO   = 0b00100000, // 自摸
    COMMAND_EAT    = 0b01000000,
    COMMAND_THROW  = 0b10000000,
}
