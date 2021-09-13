#include "guacaplus/api.hpp"
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <fmt/printf.h>
#include <spdlog/spdlog.h>

//
#include <exception>
#include <stdexcept>
#include <boost/json.hpp>


namespace guacaplus {

    namespace detail {
        constexpr int BAD_REQUEST = 400;

        void raise_for_status(cpr::Response const& response){

            if(response.status_code == 0) {
                fmt::print("Error: {0}\n", response.error.message);
                throw std::runtime_error(response.error.message);
            }
            if (response.status_code >= BAD_REQUEST) {
                fmt::print("BAD REQUEST {0}\n", response.status_code);
                throw std::runtime_error(response.error.message);
            }
        }
        auto parse_response(std::string const& response) {
            boost::json::error_code ec;
            auto json_value = boost::json::parse(response, ec);
            if( not ec) {
                return json_value.get_object();
            }
            throw std::runtime_error(ec.message());
        }

        template <typename Func, typename... Ts>
        cpr::Response request(Func method, Ts&&... ts) {
            return method(std::forward<Ts>(ts)...);
        }
    }


    GuacamoleAPI::GuacamoleAPI (std::string hostname, std::string username, std::string password,
            std::string const& default_datasource, std::string method, bool cookies):
        m_username(std::move(username)), m_password(std::move(password))
    {
        this->m_rest_api = fmt::format("{0}://{1}/api", method, hostname);
        this->authenticate(cookies, default_datasource);
    }

    void GuacamoleAPI::authenticate(bool cookies, std::string const& default_datasource) {
        const std::string url = this->m_rest_api + "/tokens";
        fmt::print("Making a request to {0}\n", url);
        cpr::Response response = cpr::Post(
            cpr::Url{url},
            cpr::Payload {
                {"username",this->m_username},
                {"password", this->m_password}
            }
        );
        //
        detail::raise_for_status(response);
        fmt::print("Request took {0}\n", response.elapsed);
        //
        auto auth_response = detail::parse_response(response.text);
        this->m_token = boost::json::value_to<std::string>(auth_response["authToken"]);
        this->m_datasources = boost::json::value_to<std::vector<std::string>>(auth_response["availableDataSources"]);
        if(cookies) {
            this->m_cookies = response.cookies;
        }
        if(not default_datasource.empty()) {
            this->datasource(default_datasource);
        }
        else {
            auto datasource = boost::json::value_to<std::string>(auth_response["dataSource"]);
            this->datasource(datasource);
        }
    }

    void GuacamoleAPI::get_connections(){

    }


    void GuacamoleAPI::datasource(std::string const& default_datasource) {

        auto it = std::find(this->m_datasources.cbegin(), this->m_datasources.cend(), default_datasource);
        if (it != this->m_datasources.end()){
            this->m_datasource = *it;
        }
        else {
            constexpr std::string_view error_format = "Datasource {0} does not exist. Possible values: {1}\n";
            std::string error_message = fmt::format(error_format, default_datasource, this->m_datasources);
            spdlog::get("guacaplus")->error(error_message);
            throw std::runtime_error(error_message);
        }
    }
    void GuacamoleAPI::cookies(const_cookie_iterator begin, const_cookie_iterator end){
        cookies_t cookies(begin, end);
        this->m_cookies = std::move(cookies);
    }



} // -----  end of namespace guacaplus -----

