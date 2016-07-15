void tplsearch(void)
{
     fseeko64(arch,0x00,SEEK_END);
     endfile=ftell(arch);
     rewind(arch);
     times=endfile/(10485760);
     for (c=0;c<times;c++)
                      {
                      fread(buffer,10485760,1,arch);
                      for (s=0;s<10485760;s++)
                      {
                         if (buffer[s]==0x00 && buffer[s+1]==0x20 && buffer[s+2]==0xAF && buffer[s+3]==0x30 && buffer[s+4]==0x00 && buffer[s+5]==0x00 && buffer[s+8]==0x00 && buffer[s+9]==0x00 && buffer[s+0x0a]==0x00 && buffer[s+0x0B]==0x0C && (buffer[s+0x0C]==0x00 buffer[s+0x0D]==0x00) 
                          {
