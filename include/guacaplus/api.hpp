/******************************************************************************
* File:             api.hpp
*
* Author:           Diego Saraiva
* Created:          09/10/21
* Description:      This contains the Guacamole API Wrapper
*****************************************************************************/
#ifndef GUACAPLUS_API_INCLUDED
#define GUACAPLUS_API_INCLUDED

#include <cpr/cpr.h>
#include <string>
#include <vector>
#include <map>

namespace guacaplus {



    // =====================================================================================
    //        Class:  GuacamoleAPI
    //  Description:
    // =====================================================================================
    class GuacamoleAPI
    {
        using cookies_t = std::map<std::string, std::string>;
        using const_cookie_iterator = cookies_t::const_iterator;
        public:
            // ====================  LIFECYCLE     =======================================
            GuacamoleAPI (std::string hostname, std::string username, std::string password,
                    std::string const& default_datasource="", std::string method="http",
                    bool cookies=false);

            // ====================  ACCESSORS     =======================================
            std::map<std::string, std::string> get_connections():
            // ====================  MUTATORS      =======================================

            // ====================  OPERATORS     =======================================
        protected:
            // ====================  METHODS       =======================================
            void datasource(std::string const& default_datasource);
            void cookies(const_cookie_iterator begin, const_cookie_iterator end);
            // ====================  DATA MEMBERS  =======================================

        private:
            // ====================  METHODS       =======================================
            void authenticate(bool load_cookies, std::string const& default_datasource);
            auto auth_request(std::string const& url, bool json_response=true);
            // ====================  DATA MEMBERS  =======================================
            std::string m_rest_api;
            std::string m_username;
            std::string m_password;
            //
            std::vector<std::string> m_datasources;
            std::string m_token;
            std::string m_datasource;
            //
            cpr::Cookies m_cookies;

    };	/* -----  end of class GuacamoleAPI  ----- */

} // -----  end of namespace guacaplus -----
#endif /* ifndef GUACAPLUS_API_INCLUDED */
