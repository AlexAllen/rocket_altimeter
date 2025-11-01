

#ifndef STORAGE

  class Storage
  {
    public:
      Storage(int sd_pin, int flash_pin);
      bool setup();
      bool transfer(char filename[]);
      bool wipe_flash();
      
    private:
      int _sd_pin;
      int _flash_pin;
  };

  #define STORAGE 1
#endif
