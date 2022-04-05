#include "floah-layout/utils/floah_error.h"

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <format>

namespace floah
{
    FloahError::FloahError(const std::string& msg, const std::source_location loc)
    {
        message = std::format("\"{}\" in {} at {}:{}", msg, loc.file_name(), loc.line(), loc.column());
    }

    const char* FloahError::what() const noexcept { return message.c_str(); }
}  // namespace floah
