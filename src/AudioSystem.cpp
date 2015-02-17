/*******************************************************************//*
 * Implementation of the AudioSystem class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-17
 * @modified    2015-02-17
 *********************************************************************/
#include "AudioSystem.h"

#include "tinyxml.h"

AudioSystem* AudioSystem::instance = NULL;

AudioSystem::AudioSystem()
:   musicEnabled(true),
    soundEnabled(true)
{
}

// Initializes AudioSystem by loading all music files
void AudioSystem::initialize()
{
    TiXmlDocument xmlDoc;

    // Return false if the XML file is not found
    if (!xmlDoc.LoadFile("../data/xml/audio/audio.xml"))
    {
        fprintf(stderr, "[ERROR] initialize(): Xml file not found.\n");
        return;
    }

    // The root element of this xml file
    TiXmlElement* rootElement = xmlDoc.RootElement();

    // The music root element of this xml file
    TiXmlElement* rootMusic = NULL;

    // Parses through Audio subelements to find the music root
    // element, then assigns it to it's own root variable
    std::string value = "Music";
    for (   TiXmlElement* e = rootElement->FirstChildElement();
            e != NULL;
            e = e->NextSiblingElement())
    {
        if (e->Value() == value)
        {
            rootMusic = e;
        }
    }

    // Return false if the music root element is not found
    if (rootMusic == NULL)
    {
        fprintf(stderr, "[ERROR] parse(): Music root element not found.\n");
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
        Mix_Music* music = Mix_LoadMUS(e->Attribute("file"));
        if (music == NULL)
        {
            printf( "Failed to load music! SDL_mixer Error: %s\n", Mix_GetError() );
            printf( "File was not loaded: %s\n", e->Attribute("file"));
        }

        // Insert key and music into table
        musicTable[key] = music;
    }
}

//void AudioSystem::toggleMusic()
//{
    //musicEnabled = !musicEnabled;
    //pauseMusic();
//}

void AudioSystem::playMusic(std::string id)
{
    // If music is enabled
    if (musicEnabled)
    {
        // If no music is playing
        if (Mix_PlayingMusic() == 0)
        {
            // Play music
            Mix_PlayMusic(musicTable[id], -1);
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
