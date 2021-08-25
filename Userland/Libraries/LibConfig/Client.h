/*
 * Copyright (c) 2021, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <ConfigServer/ConfigClientEndpoint.h>
#include <ConfigServer/ConfigServerEndpoint.h>
#include <LibCore/File.h>
#include <LibCore/Promise.h>
#include <LibCore/StandardPaths.h>
#include <LibIPC/ServerConnection.h>

namespace Config {

class Client final
    : public IPC::ServerConnection<ConfigClientEndpoint, ConfigServerEndpoint>
    , public ConfigClientEndpoint {
    C_OBJECT(Client);

public:
    String read_string(StringView domain, StringView group, StringView key, StringView fallback);
    i32 read_i32(StringView domain, StringView group, StringView key, i32 fallback);
    bool read_bool(StringView domain, StringView group, StringView key, bool fallback);

    void write_string(StringView domain, StringView group, StringView key, StringView value);
    void write_i32(StringView domain, StringView group, StringView key, i32 value);
    void write_bool(StringView domain, StringView group, StringView key, bool value);

    static Client& the();

private:
    explicit Client()
        : IPC::ServerConnection<ConfigClientEndpoint, ConfigServerEndpoint>(*this, "/tmp/portal/config")
    {
    }
};

inline String read_string(StringView domain, StringView group, StringView key, StringView fallback = {})
{
    return Client::the().read_string(domain, group, key, fallback);
}

inline i32 read_i32(StringView domain, StringView group, StringView key, i32 fallback = 0)
{
    return Client::the().read_i32(domain, group, key, fallback);
}

inline bool read_bool(StringView domain, StringView group, StringView key, bool fallback = false)
{
    return Client::the().read_bool(domain, group, key, fallback);
}

inline void write_string(StringView domain, StringView group, StringView key, StringView value)
{
    Client::the().write_string(domain, group, key, value);
}

inline void write_i32(StringView domain, StringView group, StringView key, i32 value)
{
    Client::the().write_i32(domain, group, key, value);
}

inline void write_bool(StringView domain, StringView group, StringView key, bool value)
{
    Client::the().write_bool(domain, group, key, value);
}

}
