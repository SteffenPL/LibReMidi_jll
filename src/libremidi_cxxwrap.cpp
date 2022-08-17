#include <libremidi/libremidi.hpp>

#include "jlcxx/jlcxx.hpp"
#include "jlcxx/stl.hpp"

using namespace libremidi;

JLCXX_MODULE define_julia_module(jlcxx::Module& mod)
{
    mod.add_bits<message_type>("MessageType");
    mod.set_const("INVALID", message_type::INVALID);
    mod.set_const("NOTE_OFF", message_type::NOTE_OFF);
    mod.set_const("NOTE_ON", message_type::NOTE_ON);
    mod.set_const("CONTROL_CHANGE", message_type::CONTROL_CHANGE);
    mod.set_const("START", message_type::START);
    mod.set_const("CONTINUE", message_type::CONTINUE);
    mod.set_const("STOP", message_type::STOP);
    

    mod.add_bits<API>("API");
    mod.set_const("UNSPECIFIED", API::UNSPECIFIED);
    mod.set_const("MACOSX_CORE", API::MACOSX_CORE);
    mod.set_const("LINUX_ALSA", API::LINUX_ALSA);
    mod.set_const("LINUX_ALSA_SEQ", API::LINUX_ALSA_SEQ);
    mod.set_const("LINUX_ALSA_RAW", API::LINUX_ALSA_RAW);
    mod.set_const("UNIX_JACK", API::UNIX_JACK);
    mod.set_const("WINDOWS_MM", API::WINDOWS_MM);
    mod.set_const("WINDOWS_UWP", API::WINDOWS_UWP);
    mod.set_const("EMSCRIPTEN_WEBMIDI", API::EMSCRIPTEN_WEBMIDI);
    mod.set_const("DUMMY", API::DUMMY);

    jlcxx::stl::apply_stl<API>(mod);
    
    mod.method("available_apis", std::function(available_apis));
    mod.method("default_platform_api", std::function(default_platform_api));

    mod.method("make_command", std::function(message::make_command));

    mod.add_bits<midi_error>("MidiError");
    mod.set_const("WARNING", midi_error::WARNING);
    mod.set_const("UNSPECIFIED", midi_error::UNSPECIFIED);
    mod.set_const("NO_DEVICES_FOUND", midi_error::NO_DEVICES_FOUND);
    mod.set_const("INVALID_DEVICE", midi_error::INVALID_DEVICE);
    mod.set_const("MEMORY_ERROR", midi_error::MEMORY_ERROR);
    mod.set_const("INVALID_PARAMETER", midi_error::INVALID_PARAMETER);
    mod.set_const("INVALID_USE", midi_error::INVALID_USE);
    mod.set_const("DRIVER_ERROR", midi_error::DRIVER_ERROR);
    mod.set_const("SYSTEM_ERROR", midi_error::SYSTEM_ERROR);
    mod.set_const("THREAD_ERROR", midi_error::THREAD_ERROR);

    mod.add_bits<meta_event_type>("MetaEventType");
    
    mod.add_type<message>("Message")
    .constructor<const midi_bytes&, double>()
    .method("uses_channel", &message::uses_channel)
    .method("get_channel", &message::get_channel)
    .method("is_meta_event", &message::is_meta_event)
    .method("get_meta_event_type", &message::get_meta_event_type)
    .method("get_message_type", &message::get_message_type)
    .method("is_note_on_or_off", &message::is_note_on_or_off)
    .method("size", &message::size);

    mod.method("make_command", std::function(message::make_command));
    mod.method("note_on", std::function(message::note_on));
    mod.method("note_off", std::function(message::note_off));
    mod.method("control_change", std::function(message::control_change));
    mod.method("program_change", std::function(message::program_change));

    // meta events
    mod.method("end_of_track", std::function(meta_events::end_of_track));
    mod.method("channel", std::function(meta_events::channel));
    mod.method("tempo", std::function(meta_events::tempo));
    mod.method("time_signature", std::function(meta_events::time_signature));
    mod.method("key_signature", std::function(meta_events::key_signature));
    mod.method("song_position", std::function(meta_events::song_position));

    mod.add_type<track_event>("track_event");

    jlcxx::stl::apply_stl<track_event>(mod);


    mod.method("get_version", std::function(get_version));

    mod.add_type<midi_out>("MidiOut")
    .constructor<API, const std::string&>(
        [](API api, const std::string& clientName)
        {
            return midi_out(api,clientName);
        })
    .method("get_current_api", &midi_out::get_current_api)
    .method("open_port", 
        [](midi_out& obj, unsigned int port)
        {
            return obj.open_port(port); 
        } 
        )
    .method("close_port", &midi_out::close_port)
    .method("is_port_open", &midi_out::is_port_open)
    .method("open_virtual_port", 
        [](midi_out& obj, std::string& portName)
        {
            return obj.open_virtual_port(portName); 
        } 
        )
    .method("get_port_count", &midi_out::get_port_count)
    .method("get_port_name", &midi_out::get_port_name)
    .method("send_message", 
        [](midi_out& obj, const message& msg)
        {
            obj.send_message(msg);
        }
        )
    .method("set_error_callback", &midi_out::set_error_callback)
    .method("set_client_name", [](midi_out& obj, std::string& clientName)
        {
            return obj.set_client_name(clientName); 
        } 
        )
    .method("set_port_name", [](midi_out& obj, std::string& portName)
        {
            return obj.set_port_name(portName); 
        } 
        );


    mod.add_type<midi_in>("MidiIn")
    .constructor<API, const std::string&, unsigned int>(
        [](API api, const std::string& clientName, unsigned int queueSizeLimit = 100)
        {
            return midi_in(api,clientName,queueSizeLimit);
        })
    .method("get_current_api", &midi_in::get_current_api)
    .method("open_port", 
        [](midi_in& obj, unsigned int port)
        {
            return obj.open_port(port); 
        } 
        )
    .method("close_port", &midi_in::close_port)
    .method("is_port_open", &midi_in::is_port_open)
    .method("open_virtual_port", 
        [](midi_in& obj, std::string& portName)
        {
            return obj.open_virtual_port(portName); 
        } 
        )
    .method("get_port_count", &midi_in::get_port_count)
    .method("get_port_name", &midi_in::get_port_name)
    .method("set_callback", &midi_in::set_callback)
    .method("ignore_types", &midi_in::ignore_types)
    .method("get_message", 
        [](midi_in& obj){return obj.get_message();} 
        )
    .method("set_error_callback", &midi_in::set_error_callback)
    .method("set_client_name", [](midi_in& obj, std::string& clientName)
        {
            return obj.set_client_name(clientName); 
        } 
        )
    .method("set_port_name", [](midi_in& obj, std::string& portName)
        {
            return obj.set_port_name(portName); 
        } 
        );
}
