#include <iostream>
#include <filesystem>

#include "arguments.h"
#include "files.h"
#include "decoder.h"

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
  Utils::Arguments args(argc, argv);

  if (args.get<std::string>("--input").empty()) {
    std::cerr << "[ERROR] No input file specified. Use --input <filename> to specify an input file." << std::endl;
    return 1;
  }

  if (!fs::is_regular_file(Utils::resolve_path(args.get<std::string>("--input")))) {
    std::cerr << "[ERROR] Input file does not exist: " << args.get<std::string>("--input") << std::endl;
    return 1;
  }
  
  Media::Stream stream_info = Decoder::probe(Utils::resolve_path(args.get<std::string>("--input")));

  for (const auto& [index, track] : stream_info.tracks) {
    std::visit([index](auto&& arg) {
      using T = std::decay_t<decltype(arg)>;
      if constexpr (std::is_same_v<T, Audio::Track>) {
        std::cout << "[Stream #0:" << index << "] Audio Track: " << arg.codec
                  << " - " << arg.bit_depth
                  << "-bits/" << arg.sample_rate
                  << "Hz - " << arg.channel_layout
                  << " channels - " << arg.bitrate << std::endl;
      } else if constexpr (std::is_same_v<T, Video::Track>) {
        std::cout << "[Stream #0:" << index << "] Video Track: " << arg.codec
                  << " - " << arg.width << "x" << arg.height
                  << "@" << arg.framerate
                  << " - " << arg.color_primary
                  << "/" << arg.transfer_function
                  << "/" << arg.color_space
                  << " - " << arg.pixel_format
                  << " - " << arg.bitrate << std::endl;
      } else {
        std::cout << "[Stream #0:" << index << "] Unknown Track Type" << std::endl;
      }
    }, track);
  }
  return 0;
}