#include "Data.h"
#include <Engine/Exceptions.h>
#include <Engine/Debug.h>
#include <Engine/Lib/Algorithm.h>

void SDG::Tiled::Data::LoadImpl(const Xml::XmlElement &el)
{
    String encoding, compression;
    std::vector<size_t> data;
    std::vector<Tile> tiles;
    std::vector<Chunk> chunks;

    el.Attribute("encoding", Xml::Optional).Query(encoding);
    el.Attribute("compression", Xml::Optional).Query(compression);

    // data
    String dataStr = el.Text();
    if (!compression.Empty())
    {
        throw RuntimeException(String::Format(
            "{}: SDG engine does not support compression of Tiled data yet. "
            "Compression requested: \"{}\"", SDG_FUNC, compression));
    }

    if (encoding == "csv")
    {
        auto dataArr = dataStr.Split(",\n\r ");
        for (auto &str : dataArr)
            data.emplace_back(str.ToNumber<size_t>());
    }
    else
    {
        throw RuntimeException(String::Format("{}: Tiled data encoding type "
            "[{}] not supported yet", SDG_FUNC, encoding));
    }

    for (auto e = el.FirstChild(); e; ++e)
    {
        if (e.Name() == "tile")
            tiles.emplace_back().Load(e);
        else if (e.Name() == "chunk")
            chunks.emplace_back().Load(e);
    }

    this->data = std::move(data);
    this->tiles = std::move(tiles);
    this->chunks = std::move(chunks);

    this->encoding = std::move(encoding);
    this->compression = std::move(compression);
}
