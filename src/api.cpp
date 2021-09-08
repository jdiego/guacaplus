#include "guacaplus/api.hpp"
#include <cpr/cpr.h>
#include <string>

namespace guacaplus {
    GuacamoleAPI::GuacamoleAPI (std::string const& hostname, std::string const& username, std::string const& password, std::string const& secret, bool verify)
        : m_hostname(hostname), m_username(username), m_password(password), m_secret(secret), m_verify(verify)
    {


    }
} // -----  end of namespace guacaplus -----

