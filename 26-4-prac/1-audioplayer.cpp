#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <map>
#include <limits>
#include <atomic>
#include <chrono>
#include <thread>
#include <cstdlib>

class Track {
	std::string trackName;
	std::string trackAuthor;
	std::tm dateCreate = { 0 };
	std::time_t trackDuration = 0;
	std::tm duration = { 0 };

public:
	void setTrack(std::string name, std::string author, std::tm date, std::time_t duration) {
		trackName = name;
		trackAuthor = author;
		dateCreate = date;
		trackDuration = duration;
	}

	const std::string& getName() {
		return trackName;
	}

	const std::string& getAuthor() {
		return trackAuthor;
	}

	const std::tm& getDate() {
		return dateCreate;
	}

	const std::tm& getDuration(){
		localtime_s(&duration, &trackDuration);
		return duration;
	}

	const std::time_t& getSec() {
		return trackDuration;
	}
};

class AudioPlayer {
	int trackId = 0;
	std::multimap<std::string, std::pair<int, Track>> tracksName;
	std::map<int, Track> tracksId;

public:
	void addTrack(Track* track) {
		++trackId;
		tracksName.insert({ track->getName(),{ trackId, *track } });
		tracksId.insert({ trackId, *track });
	}
	
	std::multimap<std::string, std::pair<int, Track>>& getInfo() {
		return tracksName;
	}

	std::map<int, Track>& getIds() {
		return tracksId;
	}

	int getId() {
		return trackId;
;	}
};

std::atomic<bool> isPlaying(false);
std::atomic<bool> next(false);
std::atomic<bool> paused(false);
std::atomic<bool> stop(false);

std::tm createDate(int year, int month, int day) {
	std::tm date = {0};
	date.tm_year = year - 1900;
	date.tm_mon = month - 1;
	date.tm_mday = day;
	return date;
}

std::string cmdInput(std::string label){
	std::string target;
	std::cout << label;
	getline(std::cin, target);
	return target;
}

void playing(std::map<int, Track>::iterator it) {
		std::cout << "<PLAYING>\n\n";
		std::cout << "|" << it->second.getName() << std::endl;
		std::cout << "|" << it->second.getAuthor() << std::endl;
		std::cout << "|" << std::put_time(&it->second.getDate(), "%d/%m/%Y") << std::endl;
		std::cout << "|" << std::put_time(&it->second.getDuration(), "%M:%S") << std::endl;
		isPlaying.store(true);
		paused.store(false);
		next.store(false);
		stop.store(false);

		int totalSeconds = it->second.getSec();
		for (int i = 0; i < totalSeconds; ++i) {
			while (paused.load()) {
				std::this_thread::sleep_for(std::chrono::seconds(1));
			}

			if (next.load()) {
				std::cout << "\n<TRACK STOPPED>\n";
				paused.store(false);
				isPlaying.store(false);
				break;
			}

			if (stop.load()) {
				std::cout << "\n<TRACK STOPPED>\n";
				break;
			}
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}

		if(!stop.load() && !next.load())
			std::cout << "\n\n<TRACK ENDED>\n";

		if (!next.load() && !stop.load())
			std::cout << "\nEnter operation: ";
		
		next.store(false);
		stop.store(false);
		isPlaying.store(false);
}

void createTracks(AudioPlayer* aPlayer) {
	Track* track = new Track();

	track->setTrack("Echoes of Tomorrow", "Aria", createDate(2024, 3, 15), 215);
	aPlayer->addTrack(track);

	track->setTrack("Midnight Horizon", "Cosmic Dreams", createDate(2023, 11, 2), 189);
	aPlayer->addTrack(track);

	track->setTrack("Neon Lights", "Synthwave Syndicate", createDate(2025, 1, 20), 202);
	aPlayer->addTrack(track);

	track->setTrack("Silent Whispers", "Ethereal Echo", createDate(2024, 7, 8), 240);
	aPlayer->addTrack(track);

	track->setTrack("Golden Skies", "Sunset Chillers", createDate(2023, 9, 30), 176);
	aPlayer->addTrack(track);

	track->setTrack("Last day of Summer", "Lalis dream", createDate(2009, 8, 29), 150);
	aPlayer->addTrack(track);

	track->setTrack("Last day of Summer", "TEPLAY", createDate(2019, 10, 9), 180);
	aPlayer->addTrack(track);

	delete track;
}

void start(std::map<int, Track>::iterator it, AudioPlayer* aPlayer) {
	if (it != aPlayer->getIds().end()) {
		std::thread isPlay(playing, it);
		isPlay.detach();
		std::cout << "\n";
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

int main() {
	AudioPlayer* aPlayer = new AudioPlayer();
	createTracks(aPlayer);
	srand(std::time(nullptr));

	while (true) {

		std::string cmd = cmdInput("\nEnter operation: ");
		std::pair<std::multimap<std::string, std::pair<int, Track>>::iterator, std::multimap<std::string, std::pair<int, Track>>::iterator> itName;
		std::map<int, Track>::iterator itId;

		if (cmd == "play") {
			if (!paused.load()) {
				if (!isPlaying.load()) {
					std::string name = cmdInput("Enter track name: ");
					itName = aPlayer->getInfo().equal_range(name);
					std::ptrdiff_t range = std::distance(itName.first, itName.second);

					if (range == 0) {
						std::cerr << "\n**UNKNOWN TRACK**\n";
						continue;
					}

					if (range == 1) {
						auto it = itName.first;
						itId = aPlayer->getIds().find(it->second.first);
						start(itId, aPlayer);
						continue;
					}

					if (range > 1) {
						std::cout << "\n<SELECT>\n\n";
						for (auto it = itName.first; it != itName.second; ++it)
							std::cout << it->second.first << ". " << it->second.second.getName() << " "
							<< it->second.second.getAuthor() << " " << std::put_time(&it->second.second.getDate(), "%d/%m/%Y") << " "
							<< std::put_time(&it->second.second.getDuration(), "%M:%S") << std::endl;
						std::cout << std::endl;
						int num = 0;
						std::cout << "Enter song num: ";
						std::cin >> num;
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

						if (std::cin.fail()) {
							std::cerr << "\n**INVALID VALUE**\n";
							std::cin.clear();
							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							continue;
						}
						itId = aPlayer->getIds().find(num);
						start(itId, aPlayer);
						continue;
					}
				}
				else {
					std::cerr << "\n**TRACK PLAYING ALREADY**\n";
					continue;
				}
			}
			else {
				paused.store(false);
				std::cout << "\n<PLAYBACK CONTINUE>\n";
				continue;
			}
		}

		else if (cmd == "next") {
			if (!isPlaying.load()) {
				std::cerr << "\n**NO TRACK PLAYING**\n\n";
				continue;
			}
			int tracksAm = aPlayer->getId();
			if (tracksAm == 0) {
				std::cerr << "\n**No tracks available**\n\n";
				continue;
			}
			next.store(true);
			int randId = rand() % tracksAm + 1;
			itId = aPlayer->getIds().find(randId);
			if (itId != aPlayer->getIds().end()) {
				std::this_thread::sleep_for(std::chrono::seconds(1));
				start(itId, aPlayer);
			}
			else {
				std::cerr << "\n**Track with id " << randId << " not found**\n\n";
				continue;
			}

		}

		else if (cmd == "pause") {
			if (!isPlaying.load()) {
				std::cerr << "\n**NO TRACK PLAYING**\n\n";
				continue;
			}
			paused.store(true);
			std::cout << "\n<PLAYBACK PAUSED>\n";
			continue;
		}
		
		else if (cmd == "stop") {
			if (!isPlaying.load()) {
				std::cerr << "\n**NO TRACK PLAYING**\n";
				continue;
			}
			stop.store(true);
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}

		else if (cmd == "exit") {
			if (isPlaying.load()) {
				std::cerr << "\n**FIRST STOP TRACK**\n";
				continue;
			}
			break;
		}

		else {
			std::cerr << "\n**UNKNOWN OPERATION**\n";
			continue;
		}
	}
	delete aPlayer;
}