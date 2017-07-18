#include "TextActor2D.h"
#include "MainClass.h"
#include <iostream>
#include "Texture.h"

namespace Johnny
{
	TextActor2D::TextActor2D(TTF_Font* font,const SDL_Color& color,const std::string& text) : Actor("TextActor"),
        m_text(text),
        m_font(font),
        m_color(color)
    {
        setName(text.c_str());
		m_castsShadows = false;
    }
    
	TextActor2D::~TextActor2D()
    {
        
    }
    
    bool TextActor2D::init()
    {
		Texture::initTexture2DShader(m_mainClass);
		Texture::initTexture2DBuffers();

		setShader(Texture::getTexture2DShader());

        generateText();
        return true;
    }
    
    bool TextActor2D::update()
    {
        if(m_needsUpdate)
        {
            generateText();
            m_needsUpdate = false;
        }
        return true;
    }

	bool TextActor2D::render()
	{
		Texture::renderTexture2D(m_texture, m_transform.getTranslation(), m_textureWidth, m_textureHeight);

		return true;
	}
    
    void TextActor2D::generateText()
    {
        if(m_mainClass)
        {
            if(m_texture)
            {
                delete m_texture;
                m_texture = nullptr;
            }
            
			SDL_Surface* sur = TTF_RenderText_Blended_Wrapped(m_font, m_text.c_str(), m_color, INT_MAX);

			m_textureWidth = sur->w;
			m_textureHeight = sur->h;
			m_texture = Texture::SDL_SurfaceToTexture(sur);

            SDL_FreeSurface(sur);
            
        }
        
    }
    
}