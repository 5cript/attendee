#pragma once

#include <attendee/core.hpp>
#include <attendee/upload_source.hpp>
#include <attendee/response.hpp>

#include <string>
#include <functional>
#include <memory>

namespace attendee
{
    class request
    {
    public:
        /**
         *  This constructor creates a request and initializes a curl easy instance.
         *  @warning Do not continue to use this class, if it caused an error (exception, if not disabled).
         */
        request();
        ~request();

        request(request const&) = delete;
        request(request&&) = default;
        request& operator=(request const&) = delete;
        request& operator=(request&&) = default;

        /**
         *  Adds a basic authentication header field.
         *
         *  @param name The username.
         *  @param password The password.
         *  @return *this.
         */
        request& basic_auth(std::string const& name, std::string const& password);

        /**
         *  Set the Accept-Encoding header. Curl will handle simple compressions automatically.
         *  @param encoding "identity" (non-compressed), "deflate" (zlib), "gzip" (gzip), "" (all supported by curl)
         */
        request& accept_encoding(std::string const& encoding);

        /**
         *  Set a custom header field. 
         */
        request& set_header_fields(std::vector<std::pair <std::string /*key*/, std::string /*value*/>> const& fields);

        /**
         *  When enabled, libcurl will automatically set the Referer:
         *  header field in HTTP requests where it follows a Location: redirect.
         */
        request& enable_auto_referer(bool referer);

        /**
         *  Adds a request for compressed Transfer Encoding in the outgoing HTTP request
         *  @see CURLOPT_TRANSFER_ENCODING
         */
        request& enable_transfer_encoding(bool transfer_encoding);

        /**
         *  Allow curl to automatically follow redirections (3xx headers).
         */
        request& follow(bool follow = true);

        /**
         *  Set the maximum amount of redirections. Only relevant, if follow was called.
         */
        request& max_redirects(long max);

        /**
         *  Set the long gohead parameter to 1L to make libcurl continue to send authentication (user+password) credentials when following locations,
         *  even when hostname changed
         *  @warning Seriously... dont.
         */
        request& forward_auth(bool forward = true);

        /**
         *  Shall ssl peers be verified?
         *  CURLOPT_SSL_VERIFYPEER
         */
        request& verify_peer(bool verify = true);

        /**
         *  Perform a get request on the URL.
         *
         *  @param url The url to get from.
         *  @param auto_encode use curls url encoder on url string for special characters.
         */
        request& get(std::string const& url);

        /**
         *  Setup a sink for get requests.
         *  @param sink_fn A function that gets called each time a piece of data is digestable.
         */
        request& sink(std::function <void(char*, std::size_t)> const& sink_fn);

        /**
         *  Setup a sink for get requests.
         *  @param sink_fn A string that gets appended every time data arrives.
         */
        request& sink(std::string& str);

        /**
         *  Sets CURLOPT_CUSTOMREQUEST, used for other less common http verbs (DELETE, ...).
         */
        request& verb(std::string const& verb);

        /**
         *  Finalizes everything and launches request.
         *  Returns the error as a curl error.
         */
        response perform();

        /**
         *  Pass cookies as a string. This sets the cookie header. Cannot be repeated and instead
         *  overwrites last call.
         */
        request& cookie_string(std::string const& cookies);

        /**
         *  Pass a CURL cookie file. This is READ-ONLY. Please read the curl documentation for warnings and security,
         *  because cookies will be passed to redirects etc.
         *  @see https://curl.haxx.se/libcurl/c/CURLOPT_COOKIEFILE.html
         */
        request& cookies(std::string const& cookie_file);

        /**
         *  @see https://curl.haxx.se/libcurl/c/CURLOPT_COOKIEJAR.html
         */
        request& cookie_jar(std::string const& cookie_jar);

        /**
         *  When you want to upload data, you will have to provide data to upload somehow.
         *  Derive from upload_source to make a data provider of your own, or use one of the standard ones.
         *  @warning usource must be kept alive for as long as the request is running.
         */
        template <typename SourceT, typename... Args>
        request& make_source(Args&&... args)
        {
            source_ = std::make_unique <SourceT>(std::forward <Args>(args)...);
            set_source();
            return *this;
        }

        /**
         *  Throttle download in byte per second
         */
        request& throttle_download(unsigned long long bytes_per_second);

        /**
         *  Set the method to put on url.
         *
         *  @param url The url to put to.
         *  @param auto_encode use curls url encoder on url string for special characters.
         */
        request& put(std::string const& url);

        /**
         *  Set the method to post on url. Use this after setting a sink or use chunked encoding.
         *
         *  @param url The url to post to.
         *  @param auto_encode use curls url encoder on url string for special characters.
         */
        request& post(std::string const& url, bool useChunked = false);

        /**
         *  Retrieve the handle to the curl instance. Try not to use, if there are implemented alternatives.
         *  No guarantees can be made after a curl instance has been altered for the other functions to do their work
         *  properly.
         */
        CURL* handle();

        /**
         *  Encodes url (" " -> "%20")
         */
        static std::string url_encode(std::string const& url);

        /**
         *  curlopt set url.
         */
        request& url(std::string const& url);

        /**
         *  Make curl print verbose information.
         */
        request& verbose();
    private:

        /**
         *  curl calls.
         */
        void set_source();

    private:
        CURL* instance_;
        std::function <void(char*, std::size_t)> sink_;
        std::unique_ptr <upload_source> source_;
    };
}
