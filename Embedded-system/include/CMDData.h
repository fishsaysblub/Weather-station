#ifndef __CMDDATA_H
#define __CMDDATA_H

struct CMDData
{
    uint8_t Address;
    uint8_t* Buffer = nullptr;
    uint8_t Len;

    uint8_t* OutputBuffer = nullptr;
    uint8_t OutputLen;

public:
    virtual ~CMDData()
    {
        if(OutputBuffer != nullptr)
            delete[] OutputBuffer;
    }
};

#endif