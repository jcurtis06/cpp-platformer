#version 330 core
out vec4 fragColor;
uniform sampler2D texture0;
uniform vec2 screenSize;
uniform vec2 logicalSize;
uniform float time;
uniform float shrinkSpeed;
uniform float vignetteSize;

void main()
{
    vec2 pixelCoord = gl_FragCoord.xy;

    pixelCoord.x = floor(pixelCoord.x * (logicalSize.x / screenSize.x)) * (screenSize.x / logicalSize.x);
    pixelCoord.y = floor(pixelCoord.y * (logicalSize.y / screenSize.y)) * (screenSize.y / logicalSize.y);

    vec2 uv = (pixelCoord / screenSize) * 2.0 - 1.0;
    uv.x *= screenSize.x / screenSize.y;

    float noise = sin(uv.x * 10.0 + time) * sin(uv.y * 10.0 + time);

    float dist = length(uv) + noise * 0.05;

    float vignette = step(vignetteSize - (time * shrinkSpeed), dist);

    fragColor = mix(texture(texture0, (gl_FragCoord.xy / screenSize)), vec4(1.0, 1.0, 1.0, 1.0), vignette);
}