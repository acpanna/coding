class String {

  private:
    String(unsigned short len);
    unsigned short itsLen;
    char *itsString;

  public:
    String(void);
    String(const char * const String);
    String(const String &classtring);
    ~String(void);

    char & operator[] (unsigned short offset);
    char operator[] (unsigned short offset) const;
    String operator+ (const String &classtring);
    String & operator= (const String &classtring);

    inline unsigned short GetLen(void) const { return itsLen; }
    inline const char * GetString(void) const { return itsString; }
  };
