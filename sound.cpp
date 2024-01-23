#include <string>
#include <SDL.h>
#include "sound.h"

Sound::Sound(std::string path){
    SDL_LoadWAV(path.c_str(), &spec, &audio_buf, &audio_len);
}

Sound::~Sound(){
    SDL_FreeWAV(audio_buf);
    SDL_CloseAudioDevice(dev);
}

void Sound::Tool(){
    dev = SDL_OpenAudioDevice(nullptr, 0, &spec, nullptr, SDL_AUDIO_ALLOW_CHANNELS_CHANGE );
}

void Sound::Go(){
    int status = SDL_QueueAudio(dev, audio_buf, audio_len);
    SDL_PauseAudioDevice(dev,0);
}

void Sound::End(){
    SDL_PauseAudioDevice(dev,1);
}

int Sound::Playing(){
    return SDL_GetAudioDeviceStatus(dev);
}
