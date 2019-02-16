#include <iostream>

#include <fluidsynth.h>

int handler(void* synth, fluid_midi_event_t* event)
{
    fluid_synth_handle_midi_event(synth, event);
    std::cout << fluid_midi_event_get_type(event) << "\r" << std::flush;
    return 0;
}

int main(int argc, char** argv)
{
    fluid_settings_t* settings;
    fluid_player_t* player;
    fluid_audio_driver_t* adriver;
    fluid_synth_t* synth;
    fluid_midi_event_t* event;

    settings = new_fluid_settings();
    fluid_settings_setstr(settings, "audio.driver", "pulseaudio");
    synth = new_fluid_synth(settings);
    player = new_fluid_player(synth);
    adriver = new_fluid_audio_driver(settings, synth);
    fluid_player_set_playback_callback(player, handler, synth);
    
    /* process command line arguments */
    for (int i = 1; i < argc; i++) {
        if (fluid_is_soundfont(argv[i])) {
	    fluid_synth_sfload(synth, argv[1], 1);
        }
        if (fluid_is_midifile(argv[i])) {
            fluid_player_add(player, argv[i]);
        }
    }

    fluid_player_play(player);
    fluid_player_join(player);
    delete_fluid_player(player);
    delete_fluid_audio_driver(adriver);
    delete_fluid_synth(synth);
    delete_fluid_settings(settings);
}
    
