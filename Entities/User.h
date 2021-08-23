#ifndef USER_H
#define USER_H
class User {
    private:
        const char* username;
        const char* password;
    
    public:
        User(const char*, const char*);
        const char* _username();
        const char* _password();
};
#endif