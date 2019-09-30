#version 110
#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect tex;
uniform sampler2DRect range;
uniform vec2 sampleOffset;
uniform float focalDistance;
uniform float focalRange;
const float PI = 3.1415926535897932384626433832795;
float weights[21];

//converts depth value to normalized, linear, between near and far plane
float LinearizeDepth(float zoverw){
    //todo: take near and far as uniforms
    float n = 1.0; // camera z near
    float f = 20000.0; // camera z far
    return (2.0 * n) / (f + n - zoverw * (f - n));
}

//translate a Depth texel into a focal value based on our
float FocalValue(vec2 pos)
{
    float depth = LinearizeDepth( texture2DRect(range, pos).r ) * 20000.;
    return min( abs(depth  - focalDistance) / focalRange, 1.0);
}
float colorWeight(vec4 rgba ){
	float bright = max(max(rgba.r,rgba.g),rgba.b);
	bright = bright * rgba.a;
	return bright;
}
// float gaussianFunction(int x){
// 	//float宣言はfloat3を使ったほうがメモリ効率がいい
	  
	
 
//   // Go through the remaining 8 vertical samples (4 on each side of the center)
//   	for (float i = 1.0; i <= numBlurPixelsPerSide; i++) { 
//    		avgValue += texture2D(texture, vertTexCoord.st - i * texOffset * 
//                           blurMultiplyVec) * incrementalGaussian.x;         
//     	avgValue += texture2D(texture, vertTexCoord.st + i * texOffset * 
//                           blurMultiplyVec) * incrementalGaussian.x;         
//     	coefficientSum += 2.0 * incrementalGaussian.x;
//     	incrementalGaussian.xy *= incrementalGaussian.yz;
//   	}
 
//   gl_FragColor = avgValue / coefficientSum;
// }
void main()
{
    //Gaussian Kernel
	// weights[0] = 0.01;
	// weights[1] = 0.014053461291849008;
	// weights[2] = 0.020595286319257878;
	// weights[3] = 0.028855245532226279;
	// weights[4] = 0.038650411513543079;
	// weights[5] = 0.049494378859311142;
	// weights[6] = 0.060594058578763078;
	// weights[7] = 0.070921288047096992;
	// weights[8] = 0.079358891804948081;
	// weights[9] = 0.084895951965930902;
	// weights[10] = 0.086826196862124602;
	// weights[11] = 0.084895951965930902;
	// weights[12] = 0.079358891804948081;
	// weights[13] = 0.070921288047096992;
	// weights[14] = 0.060594058578763092;
	// weights[15] = 0.049494378859311121;
	// weights[16] = 0.0386504115135431;
	// weights[17] = 0.028855245532226279;
	// weights[18] = 0.020595286319257885;
	// weights[19] = 0.014053461291849008;
	// weights[20] = 0.01;
	int samples = 40;
	vec4 sum = vec4(0.0, 0.0, 0.0,0.0);
    float rangeTexel = FocalValue( gl_TexCoord[0].st);
    vec2 blurOffset = sampleOffset * rangeTexel;
	vec2 baseOffset = blurOffset ;//* - (float(samples) / 2.0);
	vec2 offset = vec2( 0.0, 0.0 );
	//
  	// Incremental Gaussian Coefficent Calculation (See GPU Gems 3 pp. 877 - 889)
	//距離によって減衰させる
	//float centerWeight = (1. - abs( FocalValue(gl_TexCoord[0].st + baseOffset )  - rangeTexel) );
	float sigma = 15.;// * centerWeight;
  	vec3 incrementalGaussian;
  	incrementalGaussian.x = 1.0 / (sqrt(2.0 * PI) * sigma);
  	incrementalGaussian.y = exp(-0.5 / (sigma * sigma));
  	incrementalGaussian.z = incrementalGaussian.y * incrementalGaussian.y;
	
  	float coefficientSum = 0.0;
  	//avgValue += texture2D(texture, vertTexCoord.st) * incrementalGaussian.x;
  	//coefficientSum += incrementalGaussian.x;
  	//incrementalGaussian.xy *= incrementalGaussian.yz;
//    int samples = (fast == 1) ? 11 : 21;
    vec4 texelCenter = texture2DRect( tex, gl_TexCoord[0].st + baseOffset + offset ) * 
		incrementalGaussian.x *
		(1. - abs( FocalValue(gl_TexCoord[0].st + baseOffset + offset)  - rangeTexel) );
	sum += texelCenter;
	coefficientSum += 2.0 * incrementalGaussian.x;
  	incrementalGaussian.xy *= incrementalGaussian.yz;
	offset += blurOffset;
    //iterato through a number of samples
	for( int s = 0; s < samples; ++s ) {
        //sample the surrounding pixels and blend them into the total with the gaussian weight
        //if fast is off, we weight the blur amount by the focal difference from the center point
        //which helps make in focus items 'pop' and avoid color bleeding between focal depths
        vec4 texelPosi = 
		texture2DRect( tex, gl_TexCoord[0].st + baseOffset + offset ) * 
		incrementalGaussian.x; 
		//(1. - abs( FocalValue(gl_TexCoord[0].st + baseOffset + offset)  - rangeTexel) );
		vec4 texelNega = 
		texture2DRect( tex, gl_TexCoord[0].st + baseOffset - offset ) * 
		incrementalGaussian.x; 
		//(1. - abs( FocalValue(gl_TexCoord[0].st + baseOffset - offset)  - rangeTexel) );
        sum += texelPosi;
		sum += texelNega;
		coefficientSum += 2.0 * incrementalGaussian.x;
  		incrementalGaussian.xy *= incrementalGaussian.yz;
		offset += blurOffset;
	}
    
	gl_FragColor = ( sum  ) * gl_Color ;
    //gl_FragColor.a = gl_Color.a;
}