#ifndef TSXPARSER_H
#define TSXPARSER_H

#include <string>
#include <vector>
#include <utility>
#include <map>

#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_utils.hpp"

namespace TSX {
  class Parser
  {
    public:
      Parser( const char* filename );
      Parser();
      virtual ~Parser();

      bool load( const char* filename );

      struct TilesetImage {
        std::string source;
        std::string transparentColor;
        unsigned int width;
        unsigned int height;
      };

      struct Tileset {
        std::string name;
        unsigned int tileWidth;
        unsigned int tileHeight;
        unsigned int spacing;
        unsigned int margin;
        int offsetX;
        int offsetY;
		int noOfTiles;
		int columns;
		int rows;

        std::map<std::string, std::string> property;

        TilesetImage image;
      };

      struct Terrain {
        std::string name;
        unsigned int tile;
        std::map<std::string, std::string> property;
      };

      struct Tile {
        unsigned int id;
        std::vector<unsigned int> terrain;
        std::map<std::string, std::string> property;

		bool _hasAnimations = false;
		std::vector<unsigned int> _animatedTileID;
		unsigned int _frameDuration;

		bool _collidable = false;
      };

      Tileset tileset;
      std::vector<Terrain> terrainList;
      std::vector<Tile> tileList;
  };
}
#endif // TSXPARSER_H
