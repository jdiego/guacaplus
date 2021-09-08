#ifndef GUACAPLUS_API_INCLUDED
#define GUACAPLUS_API_INCLUDED

#include <string>
#include <string_view>
namespace guacaplus {
    class GuacamoleAPI
    {
        public:
            GuacamoleAPI (std::string const& hostname, std::string const& username,
                    std::string const& password, std::string const& secret,
                    bool verify=true);

        private:
            std::string m_hostname;
            std::string m_username;
            std::string m_password;
            std::string m_secret;
            std::string m_rest_api;
            bool verify;
    };

} // -----  end of namespace guacaplus -----
#endif /* ifndef GUACAPLUS_API_INCLUDED */
