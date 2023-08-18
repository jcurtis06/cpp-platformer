#include "animation.hpp"

Animation::Animation(const Texture2D& texture, int h_frames, int v_frames, int start_frame, int end_frame, float frame_duration)
        : texture(texture), h_frames(h_frames), v_frames(v_frames), start_frame(start_frame), end_frame(end_frame), frame_duration(frame_duration) { current_frame = start_frame; }
void Animation::draw(Vector2i pos) {
    timer += GetFrameTime();

    if (timer >= frame_duration) {
        current_frame++;
        timer = 0;
    }

    if (current_frame > end_frame) {
        current_frame = start_frame;
    }

    int x = current_frame % h_frames;
    int y = current_frame / h_frames;

    Rectangle source{
            (float)(texture.width / h_frames * x),
            (float)(texture.height / v_frames * y),
            (float)(texture.width / h_frames),
            (float)(texture.height / v_frames)
    };

    DrawTextureRec(texture, source, { (float)pos.x, (float)pos.y }, WHITE);
}
