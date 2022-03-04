#include <sentry.h>

static void test_sentry_init(void)
{
    sentry_options_t *options = sentry_options_new();
    sentry_options_set_release(options, "my-test-project@0.0.1");
    sentry_options_set_symbolize_stacktraces(options, 1);
    sentry_options_set_environment(options, "development");
    sentry_options_set_release(options, "test-example-release");
    sentry_options_add_attachment(options, "./Makefile");
    
    sentry_init(options);

    sentry_set_tag("test-tag", "test-value");
    
    sentry_value_t user = sentry_value_new_object();
    sentry_value_set_by_key(user, "ip_address", sentry_value_new_string("{{auto}}"));
    sentry_set_user(user);
}

static void test_sentry_fini(void) 
{
    sentry_close();
}
