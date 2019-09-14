
#ifndef G_SENDER
#define G_SENDER
#define GS_SERIAL_LOG_1         // Print to Serial only server response
//#define GS_SERIAL_LOG_2       //  Print to Serial client commands and server response
#include <WiFiClientSecure.h>

class Gsender
{
    protected:
        Gsender();
    private:
        const int SMTP_PORT = 465;
        const char* SMTP_SERVER = "smtp.gmail.com";
        const char* EMAILBASE64_LOGIN = "Ym9vbmVlZHNhdHRlbnRpb25AZ21haWwuY29t"; //fill with email account that you want to get emails from (must be base64 encoded)
        const char* EMAILBASE64_PASSWORD = "-------"; //fill password for that email account (must be base64 encoded)
        const char* FROM = "booneedsattention@gmail.com"; //fill with email account that you want to get emails from
        const char* _error = nullptr;
        char* _subject = nullptr;
        String _serverResponce;
        static Gsender* _instance;
        bool AwaitSMTPResponse(WiFiClientSecure &client, const String &resp = "", uint16_t timeOut = 10000);

    public:
        static Gsender* Instance();
        Gsender* Subject(const char* subject);
        Gsender* Subject(const String &subject);
        bool Send(const String &to, const String &message);
        String getLastResponce();
        const char* getError();
};
#endif // G_SENDER
