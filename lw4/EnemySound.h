
#pragma once
#include <SFML/Audio.hpp>
#include <vector>
#include <random>
#include <memory>
#include <chrono>

class EnemySound
{
public:
	EnemySound()
	{
		m_randomEngine.seed(std::chrono::system_clock::now().time_since_epoch().count());

		LoadSound("hello.mp3");
		LoadSound("dead.mp3");
		LoadSound("duck.mp3");
		LoadSound("papa.mp3");
		LoadSound("questions.mp3");

		if (m_sounds.empty())
		{
			throw std::runtime_error("Failed to load any enemy sounds");
		}

		m_nextSoundTime = std::chrono::steady_clock::now();
		ScheduleNextSound();
	}

	void Update()
	{
		auto now = std::chrono::steady_clock::now();

		if (!m_currentSound && now >= m_nextSoundTime)
		{
			PlayRandomSound();
		}
		else if (m_currentSound && m_currentSound->getStatus() == sf::Sound::Stopped)
		{
			m_currentSound.reset();
			ScheduleNextSound();
		}
	}

private:
	std::vector<sf::SoundBuffer> m_sounds;
	std::unique_ptr<sf::Sound> m_currentSound;
	std::default_random_engine m_randomEngine;
	std::chrono::steady_clock::time_point m_nextSoundTime;

	void LoadSound(const std::string& filename)
	{
		sf::SoundBuffer buffer;
		if (buffer.loadFromFile(filename))
		{
			m_sounds.push_back(std::move(buffer));
		}
	}

	void PlayRandomSound()
	{
		if (m_sounds.empty()) return;

		std::uniform_int_distribution<size_t> dist(0, m_sounds.size() - 1);
		size_t randomIndex = dist(m_randomEngine);

		m_currentSound = std::make_unique<sf::Sound>();
		m_currentSound->setBuffer(m_sounds[randomIndex]);
		m_currentSound->play();
	}

	void ScheduleNextSound()
	{
		m_nextSoundTime = std::chrono::steady_clock::now() + std::chrono::seconds(3);
	}
};