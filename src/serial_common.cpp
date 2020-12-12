//Convert float to char and send it through serial port
unsigned char *float2char(float f,unsigned char *s)
{
 unsigned char *p;
 p = (unsigned char *)&f;

    *s = *p;

    *(s+1) = *(p+1);

    *(s+2) = *(p+2);

    *(s+3) = *(p+3);
return p;
}

