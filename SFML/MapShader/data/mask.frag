uniform sampler2D mask;
uniform sampler2D texture;
uniform vec4 mask_color;

void main()
{
    // lookup the pixel in the texture
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    vec4 mask_pixel = texture2D(mask, gl_TexCoord[0].xy);

    // multiply it by the color
    //gl_FragColor = gl_Color;
    gl_FragColor = pixel * mask_color;
	gl_FragColor.a = mask_pixel.r;
}
