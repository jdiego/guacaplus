#include "guacaplus/api.hpp"
#include <fmt/core.h>
#include <fmt/printf.h>
#include <cpr/cpr.h>
#include <exception>
#include <stdexcept>

namespace guacaplus {
    
    namespace detail {
        constexpr int BAD_REQUEST = 400; 
        void raise_for_status(cpr::Response const& response){
            if(response.status_code == 0){
                fmt::fprintf(stderr, "{0}\n", response.error.message);
                throw std::runtime_error(response.error.message);
            }
            if (response.status_code >= BAD_REQUEST) {
                fmt::fprintf(stderr, "Error [{0}] making request\n", response.status_code); 
                throw std::runtime_error(response.error.message);
            } 
        }
    }


    GuacamoleAPI::GuacamoleAPI (std::string hostname, std::string username, std::string password, 
            std::string secret, std::string method, [[maybe_unused]] std::string url_path, std::string default_datasource,
            [[maybe_unused]] bool cookies, bool verify):
        m_username(std::move(username)), m_password(std::move(password)), 
        m_secret(std::move(secret)), m_verify(verify)
    {
        this->m_rest_api = fmt::format("{0}://{1}/{2}/api", method, hostname, url_path);
        this->authenticate();
        //this->m_cookies = cookies ? response.cookies: 
    }

    void GuacamoleAPI::authenticate() {
        auto url = this->m_rest_api + "/tokens";
        cpr::Response response = cpr::Post(
            cpr::Url{url},
            cpr::Payload { 
                {"username",this->m_username},
                {"password", this->m_password} 
            }
        );
        //
        detail::raise_for_status(response);
        
    }

} // -----  end of namespace guacaplus -----

