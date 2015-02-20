/*******************************************************************//*
 * Implementation of the AudioSystem class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-17
 * @modified    2015-02-20
 *********************************************************************/
#include "AudioSystem.h"

#include <cstdio>

#include "tinyxml.h"
#include "Util.h"

AudioSystem* AudioSystem::instance = NULL;

AudioSystem::AudioSystem()
:   musicPlayingState(true),
    musicEnabled(true),
    soundEnabled(true),
    currentMusic(NULL)
{
    //printf("music volume = %d\n", Mix_VolumeMusic(-1));
    Mix_VolumeMusic(64);
}

// Initializes AudioSystem by loading all music files
void AudioSystem::initialize()
{
    TiXmlDocument xmlDoc;

    // Return false if the XML file is not found
    if (!xmlDoc.LoadFile(Util::fix_path("../data/xml/audio/audio.xml").c_str()))
    {
        printf("[ERROR] initialize(): Xml file not found.\n");
        return;
    }

    // The root element of this xml file
    TiXmlElement* rootElement = xmlDoc.RootElement();

    // The music root element of this xml file
    TiXmlElement* rootMusic = NULL;

    //The sound root element of this xml file
    TiXmlElement* rootSound = NULL;

    // Parses through Audio subelements to find the music root
    // element, then assigns it to it's own root variable
    std::string valueMusic = "Music";
    std::string valueSound = "Sound";
    for (   TiXmlElement* e = rootElement->FirstChildElement();
            e != NULL;
            e = e->NextSiblingElement())
    {
        if (e->Value() == valueMusic)
        {
            rootMusic = e;
        }
        else if (e->Value() == valueSound)
        {
            rootSound = e;
        }
    }

    // Return false if the music root element is not found
    if (rootMusic == NULL)
    {
        printf("[ERROR] parse(): Music root element not found.\n");
        return;
    }

    // Return false if thesSound root element is not found
    if (rootSound == NULL)
    {
        printf("[ERROR] parse(): Sound root element not found.\n");
        return;
    }

    // Parses through subelements of the music root element and
    // fills loads audio files into table
    for (   TiXmlElement* e = rootMusic->FirstChildElement();
            e != NULL;
            e = e->NextSiblingElement())
    {
        // Load key
        std::string key = e->Attribute("id");

        // Load music
        Mix_Music* music = Mix_LoadMUS(Util::fix_path(e->Attribute("file")).c_str());
        if (music == NULL)
        {
            printf( "Failed to load music! SDL_mixer Error: %s\n", Mix_GetError() );
            printf( "File was not loaded: %s\n", e->Attribute("file"));
        }

        // Insert key and music into table
        musicTable[key] = music;
    }

    for (   TiXmlElement* e = rootSound->FirstChildElement();
            e != NULL;
            e = e->NextSiblingElement())
    {
        // Load key
        std::string key = e->Attribute("id");

        // Load Sound
        Mix_Chunk* sound = Mix_LoadWAV(Util::fix_path(e->Attribute("file")).c_str());
        if (sound == NULL)
        {
            printf( "Failed to load sound! SDL_mixer Error: %s\n", Mix_GetError() );
            printf( "File was not loaded: %s\n", e->Attribute("file"));
        }

        if (e->Attribute("volume") != NULL)
        {
            char volume = atoi(e->Attribute("volume"));
            Mix_VolumeChunk(sound, volume);
        }
        // Insert key and Sound into table
        soundTable[key] = sound;
    }
}

void AudioSystem::setMusicPlayingState(bool status)
{
    musicPlayingState = status;
}

void AudioSystem::toggleMusic()
{
    if (musicEnabled)
    {
        musicEnabled = false;
        pauseMusic();
    }
    else
    {
        musicEnabled = true;
        playMusic();
    }
}

void AudioSystem::toggleSound()
{
    if (soundEnabled)
    {
        soundEnabled = false;
    }
    else
    {
        soundEnabled = true;
    }
}

bool AudioSystem::getMusicStatus()
{
    return musicEnabled;
}

bool AudioSystem::getSoundStatus()
{
    return soundEnabled;
}

void AudioSystem::loadMusic(std::string id)
{
    currentMusic = musicTable[id];
}

void AudioSystem::playMusic()
{
    // If music is enabled
    if (musicEnabled && musicPlayingState)
    {
        // If no music is playing
        if (Mix_PlayingMusic() == 0)
        {
            // Play music
            Mix_FadeInMusic(currentMusic, -1, 1000);
        }
        // If music is paused
        else if (Mix_PausedMusic() == 1)
        {
            // Resume music
            Mix_ResumeMusic();
        }
    }
}

void AudioSystem::pauseMusic()
{
    // If music is playing
    if (Mix_PlayingMusic() == 1)
    {
        // Pause music
        Mix_PauseMusic();
    }
}

void AudioSystem::stopMusic()
{
    // Stops music
    Mix_HaltMusic();
}

void AudioSystem::playSound(std::string id)
{
    // If sound is enabled
    if (soundEnabled)
    {
        // Play the sound on any available channel, no repeat
        Mix_PlayChannel(-1, soundTable[id], 0);
    }
}

// Terminates AudioSystem by freeing all music files
void AudioSystem::terminate()
{
    std::map<std::string, Mix_Music*>::iterator musicIterator;
    for (   musicIterator=musicTable.begin();
            musicIterator!=musicTable.end();
            musicIterator++)
    {
        Mix_FreeMusic((*musicIterator).second);
    }

    std::map<std::string, Mix_Chunk*>::iterator soundIterator;
    for (   soundIterator=soundTable.begin();
            soundIterator!=soundTable.end();
            soundIterator++)
    {
        Mix_FreeChunk((*soundIterator).second);
    }
}
