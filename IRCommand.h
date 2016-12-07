#ifndef IRCOMMAND_H
#define IRCOMMAND_H

// ucon ircommand
//#define IR_UP       0x40
//#define IR_DOWN     0x19
//#define IR_LEFT     0x07
//#define IR_RIGHT    0x09
//#define IR_ENTER    0x15

//#define IR_MAINFORM 0x45
//#define IR_ECG      0x47
//#define IR_VISUALCHART 0x1C
//#define IR_COLORCHART 0x08
//#define IR_PATIENTTYPE 0x44
//#define IR_CLEAR    0x42
//#define IR_BLOODPRE 0x46
//#define IR_PRINT    0x52
//#define IR_VOICE    0x5A

// the first ircommand
//#define IR_MODEL    0x45
//#define IR_MODER    0x47
//#define IR_PGUP     0x44
//#define IR_PGDOWN   0x43
//#define IR_YES      0x16


#define IR_UP       0x03
#define IR_DOWN     0x02
#define IR_LEFT     0x0E
#define IR_RIGHT    0x1A
#define IR_ENTER    0x07

#define IR_MAINFORM 0x48
#define IR_ECG      0x58
#define IR_VISUALCHART 0x14
#define IR_COLORCHART 0x13
//#define IR_PATIENTTYPE 0x44
#define IR_ADULT    0x0E
#define IR_CHILD    0X1A
#define IR_CLEAR    0x02
#define IR_BLOODPRE 0x03
#define IR_PRINT    0x5C
#define IR_VOICE    0x0B
#define IR_VISUALLOW 0X01


//#define IR_SYSRESET 0X52
//#define IR_NO       0x0d
//#define IR_SHOW     0x03
//#define IR_CLEAR    0x05
#define PACKID_IR   0xFE
//#define PACKID_ACCU 0xFF
#define PACKEND     0xF0
#define IR_SEND     0x4A

#endif // IRCOMMAND_H
