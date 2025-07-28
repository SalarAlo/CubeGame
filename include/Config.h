#pragma once

constexpr int CHUNK_SIZE { 16 };
constexpr int CHUNK_HEIGHT { 16 };

constexpr int CHUNK_VOLUME { CHUNK_SIZE * CHUNK_SIZE * CHUNK_HEIGHT };
constexpr int CHUNK_PLANE { CHUNK_SIZE * CHUNK_SIZE };

