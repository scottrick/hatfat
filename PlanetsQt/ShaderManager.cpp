#include "ShaderManager.h"

#include "BrickProgram.h"
#include "CubeProgram.h"
#include "Options.h"
#include "PlanetProgramOne.h"
#include "StripeProgram.h"
#include "TestTextureProgram.h"
#include "ToonProgram.h"

ShaderManager::ShaderManager()
{
    Init();
}

ShaderManager::~ShaderManager()
{
    ClearPrograms();
}

void ShaderManager::ClearPrograms()
{
    vector<ShaderProgram *>::iterator iter = m_Programs.begin();

    while (iter != m_Programs.end())
    {
        (*iter)->Release();
    }

    m_Programs.clear();
}

ShaderProgram *ShaderManager::GetActiveProgram()
{
    return (*m_ProgramIter);
}

void ShaderManager::Init()
{
    //ShaderProgram *pTextureProgram    = new TestTextureProgram("../shaders/texture.frag", "../shaders/texture.vert", "Texture");
    ShaderProgram *pDirLightOne         = new ShaderProgram("../shaders/dir_light1.frag", "../shaders/dir_light1.vert", "DirLight1");
    ShaderProgram *pPhong               = new ShaderProgram("../shaders/phong.frag", "../shaders/phong.vert", "Phong");
//    ShaderProgram *pDiffuse             = new ShaderProgram("../shaders/diffuse.frag", "../shaders/diffuse.vert", "Diffuse");
    ShaderProgram *pRedBumpProgram      = new ShaderProgram("../shaders/red_bumpy.frag", "../shaders/red_bumpy.vert", "RedBumpy");
    ShaderProgram *pToonProgram         = new ToonProgram("../shaders/toon.frag", "../shaders/default.vert", "Toon");
    ShaderProgram *pWNormalsProgram     = new ShaderProgram("../shaders/normals.frag", "../shaders/normals.vert", "Normals");
    ShaderProgram *pBrickProgram        = new BrickProgram("../shaders/brick.frag", "../shaders/brick.vert", "Brick");
    ShaderProgram *pCubeProgram         = new CubeProgram("../shaders/cube.frag", "../shaders/cube.vert", "Cubes!");
    ShaderProgram *pStripeProgram       = new StripeProgram("../shaders/stripes.frag", "../shaders/stripes.vert", "Stripes");
    m_pPlanetProgram                    = new PlanetProgramOne("../shaders/planet1.frag", "../shaders/planet1.vert", "Planet1");
    m_pPlanetTest                       = new PlanetProgramOne("../shaders/planet2.frag", "../shaders/planet2.vert", "PlanetTest");

    m_Programs.push_back(m_pPlanetProgram);
    m_Programs.push_back(m_pPlanetTest);
    m_Programs.push_back(pPhong);
//    m_Programs.push_back(pDiffuse);
    m_Programs.push_back(pDirLightOne);
    m_Programs.push_back(pRedBumpProgram);
    m_Programs.push_back(pToonProgram);
    m_Programs.push_back(pWNormalsProgram);
    m_Programs.push_back(pBrickProgram);
    m_Programs.push_back(pStripeProgram);
    m_Programs.push_back(pCubeProgram);
    //m_Programs.push_back(pTextureProgram);

    m_ProgramIter = m_Programs.begin();
    (*m_ProgramIter)->ShowOptions();
}

void ShaderManager::NextProgram()
{
    if (m_ProgramIter < m_Programs.end())
    {
        ShaderProgram *prevProgram = *m_ProgramIter;

        m_ProgramIter++;

        if (m_ProgramIter == m_Programs.end())
        {
            m_ProgramIter--;
        }
        else
        { //switching to a new program, so change the visible options
            prevProgram->HideOptions();
            (*m_ProgramIter)->ShowOptions();
        }
    }
}

void ShaderManager::PrevProgram()
{
    if (m_ProgramIter != m_Programs.begin())
    {
        (*m_ProgramIter)->HideOptions();
        m_ProgramIter--;
        (*m_ProgramIter)->ShowOptions();
    }
}
