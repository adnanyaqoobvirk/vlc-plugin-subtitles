#define MODULE_STRING "subtitles"

#include <stdlib.h>

/* VLC core API headers */
#include <vlc_common.h>
#include <vlc_plugin.h>
#include <vlc_interface.h>

/* Forward declarations */
static int Open(vlc_object_t *);
static void Close(vlc_object_t *);

/* Module descriptor */
vlc_module_begin()
    set_shortname("Subtitles")
    set_description("Extra Features for Subtitles")
    set_capability("interface", 0)
    set_callbacks(Open, Close)
    set_category(CAT_INTERFACE)
vlc_module_end ()

/* Internal state for an instance of the module */
struct intf_sys_t
{
    char *who;
};

/**
 * Starts our example interface.
 */
static int Open(vlc_object_t *obj)
{
    intf_thread_t *intf = (intf_thread_t *)obj;
    intf->p_module

    /* Allocate internal state */
    intf_sys_t *sys = (intf_sys_t *)malloc(sizeof (intf_sys_t));
    if (unlikely(sys == NULL))
        return VLC_ENOMEM;
    intf->p_sys = sys;

    /* Read settings */
    char *who = var_InheritString(intf, "hello-who");
    if (who == NULL)
    {
        msg_Err(intf, "Nobody to say hello to!");
        goto error;
    }
    sys->who = who;

    msg_Info(intf, "Hello %s!", who);
    return VLC_SUCCESS;

    error:
    free(sys);
    return VLC_EGENERIC;
}

/**
 * Stops the interface.
 */
static void Close(vlc_object_t *obj)
{
    intf_thread_t *intf = (intf_thread_t *)obj;
    intf_sys_t *sys = intf->p_sys;

    msg_Info(intf, "Good bye!");

    /* Free internal state */
    free(sys->who);
    free(sys);
}