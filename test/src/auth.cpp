#include "guacaplus/api.hpp"
#include <doctest/doctest.h>
#include <spdlog/spdlog.h>
#include "spdlog/sinks/stdout_color_sinks.h"
#include <string>


TEST_CASE("Authentication") {
    using namespace guacaplus;
    const auto *url =  "banos.ifrn.local:8800";
    const auto *username = "2077349";
    const auto *password = "#S3mP@c13nc14";

    auto guaca_logger = spdlog::stderr_color_mt("gaucaplus");
    spdlog::register_logger(guaca_logger);

    SUBCASE("Testing the authenticate routine") {
        GuacamoleAPI api(url, username, password);
    }

}
