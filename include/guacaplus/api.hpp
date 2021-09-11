/******************************************************************************
* File:             api.hpp
*
* Author:           Diego Saraiva
* Created:          09/10/21
* Description:      This contains the Guacamole API Wrapper
*****************************************************************************/
#ifndef GUACAPLUS_API_INCLUDED
#define GUACAPLUS_API_INCLUDED

#include <string>
#include <vector>


namespace guacaplus {
    // =====================================================================================
    //        Class:  GuacamoleAPI
    //  Description:
    // =====================================================================================
    class GuacamoleAPI
    {
        public:
            // ====================  LIFECYCLE     =======================================
            GuacamoleAPI (std::string hostname, std::string username,
                    std::string password, std::string secret, std::string method,
                    std::string url_path="/", std::string default_datasource="", 
                    bool cookies=false, bool verify=true);
            // ====================  ACCESSORS     =======================================

            // ====================  MUTATORS      =======================================

            // ====================  OPERATORS     =======================================
        protected:
            // ====================  METHODS       =======================================

            // ====================  DATA MEMBERS  =======================================

        private:
            // ====================  METHODS       =======================================
            void authenticate();
            // ====================  DATA MEMBERS  =======================================
            std::string m_rest_api;
            std::string m_username;
            std::string m_password;
            std::string m_secret;
            bool m_verify;
            //
            std::vector<std::string> m_datasources;
            std::string m_token;

    };	/* -----  end of class GuacamoleAPI  ----- */

} // -----  end of namespace guacaplus -----
#endif /* ifndef GUACAPLUS_API_INCLUDED */
