#include "application.h"

static const cinder::ivec2 WindowSize{640, 480};

Application::Application()
{}

void Application::prepareSettings(Settings* settings)
{
	settings->setWindowSize(WindowSize);
	settings->setFrameRate(35.0f);
	settings->setResizable(false);
	settings->setFullScreen(false);
}

void Application::keyDown(ci::app::KeyEvent keyEvent)
{
    switch (keyEvent.getCode())
    {
        case keyEvent.KEY_UP:
        {
            ChangeDirectionUp();
            break;
        }
        case keyEvent.KEY_DOWN:
        {
            ChangeDirectionDown();
            break;
        }
        case keyEvent.KEY_LEFT:
        {
            ChangeDirectionLeft();
            break;
        }
        case keyEvent.KEY_RIGHT:
        {
            ChangeDirectionRight();
            break;
        }
        case keyEvent.KEY_RETURN:
        {
            if (keyEvent.isAltDown())
            {
                mDisplayString = FULL_SCREEN_MESSAGE;
                cinder::app::setFullScreen(true);
            }
            break;
        }
        case keyEvent.KEY_ESCAPE:
        {
            if (isFullScreen())
            {
                setFullScreen(false);
                mDisplayString = "SNAKE";
            }
            else
                {
                quit();
            }
            break;
        }
        case keyEvent.KEY_F11:
        {
            setFullScreen(!isFullScreen());
            mDisplayString = isFullScreen() ? FULL_SCREEN_MESSAGE : "SNAKE";
            break;
        }
    }
}

void Application::setup()
{
    mTextureFontRef = cinder::gl::TextureFont::create( cinder::Font("Times New Roman", 24) );
}

void Application::draw()
{
    cinder::gl::clear();

    cinder::gl::setMatricesWindow( cinder::app::getWindowSize() );
    cinder::gl::enableAlphaBlending();
    cinder::gl::clear( cinder::Color( 0, 0, 0 ) );

    cinder::gl::color( cinder::ColorA( 1, 0.9f, 0.25f, 1.0f ) );

    cinder::vec2 offset = cinder::vec2( 0 );
    auto renderSize = mTextureFontRef->measureString(mDisplayString);
    mTextureFontRef->drawString(mDisplayString, cinder::vec2( getWindowWidth() - renderSize.x - 10, getWindowHeight() - mTextureFontRef->getDescent() ) + offset);
}

void Application::update()
{}

void Application::ChangeDirectionUp()
{
    mDisplayString = "UP";
}
void Application::ChangeDirectionDown()
{
    mDisplayString = "DOWN";
}
void Application::ChangeDirectionLeft()
{
    mDisplayString = "LEFT";
}
void Application::ChangeDirectionRight()
{
    mDisplayString = "RIGHT";
}

CINDER_APP(Application, ci::app::RendererGl(ci::app::RendererGl::Options().msaa(16)), &Application::prepareSettings)
