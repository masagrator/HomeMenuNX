#include "homescreen.h"
#include <giflib/CEV_gif.h>

homescreen::homescreen(SDL_Renderer *r) : base_screen(r){};

CEV_GifAnim *animation;
SDL_Texture *actTexture = NULL;

SDL_Rect blitPos = { 0, 0, 1280, 720 };

void homescreen::init()
{

  animation = CEV_gifAnimLoad("test.gif", renderer);

  actTexture = CEV_gifTexture(animation);
  CEV_gifLoopMode(animation, GIF_REPEAT_FOR);

  std::string name;
  SDL_Rect temp_rect = {0, 0, 1280, 720};
  int w, h = 0;

  // wallpaper
  auto pair = std::pair<SDL_Texture *, SDL_Rect>(create_texture("wallpaper", "wallpaper.png"), temp_rect);
  textureMap.insert(std::make_pair("wallpaper", pair));

  // icons menu
  temp_rect = {20, 200, 240, 500};
  pair = std::pair<SDL_Texture *, SDL_Rect>(create_texture("icons_bg", "icons_bg.png"), temp_rect);
  textureMap.insert(std::make_pair("icons_bg", pair));
  // icons
  for (auto i = 0; i < 6; i++)
  {
    switch (i)
    {
    case 0:
      name = "news";
      temp_rect = {60, 240, 35, 33};
      break;
    case 1:
      name = "e_shop";
      temp_rect = {62, 316, 30, 30};
      w = 30;
      h = 30;
      break;
    case 2:
      name = "album";
      temp_rect = {60, 400, 35, 23};
      w = 35;
      h = 23;
      break;
    case 3:
      name = "controller";
      temp_rect = {60, 470, 34, 33};
      w = 34;
      h = 33;
      break;
    case 4:
      name = "settings";
      temp_rect = {60, 550, 35, 36};
      w = 35;
      h = 36;
      break;
    case 5:
      name = "power";
      temp_rect = {65, 630, 28, 33};
      w = 28;
      h = 33;
      break;
    }
    pair = std::pair<SDL_Texture *, SDL_Rect>(create_texture(name, name + ".png"), temp_rect);
    textureMap.insert(std::make_pair(name, pair));
  }

  temp_rect = {45, 290, 190, 5};
  std::string f = "seperator";
  name = "seperator";
  pair = std::pair<SDL_Texture *, SDL_Rect>(create_texture(name, name + ".png"), temp_rect);
  textureMap.insert(std::make_pair(name, pair));
  temp_rect = {45, 370, 190, 5};
  name = "seperator2";
  pair = std::pair<SDL_Texture *, SDL_Rect>(create_texture(name, f + ".png"), temp_rect);
  textureMap.insert(std::make_pair(name, pair));
  temp_rect = {45, 450, 190, 5};
  name = "seperator3";
  pair = std::pair<SDL_Texture *, SDL_Rect>(create_texture(name, f + ".png"), temp_rect);
  textureMap.insert(std::make_pair(name, pair));
  temp_rect = {45, 530, 190, 5};
  name = "seperator4";
  pair = std::pair<SDL_Texture *, SDL_Rect>(create_texture(name, f + ".png"), temp_rect);
  textureMap.insert(std::make_pair(name, pair));
  temp_rect = {45, 610, 190, 5};
  name = "seperator5";
  pair = std::pair<SDL_Texture *, SDL_Rect>(create_texture(name, f + ".png"), temp_rect);
  textureMap.insert(std::make_pair(name, pair));

  // top menu
  // bg
  name = "top_bg";
  temp_rect = {420, 50, 425, 50};
  pair = std::pair<SDL_Texture *, SDL_Rect>(create_texture(name, name + ".png"), temp_rect);
  textureMap.insert(std::make_pair(name, pair));

  name = "handheld";
  temp_rect = {445, 45, 58, 58};
  pair = std::pair<SDL_Texture *, SDL_Rect>(create_texture(name, name + ".png"), temp_rect);
  textureMap.insert(std::make_pair(name, pair));

  name = "wifi";
  temp_rect = {720, 63, 20, 20};
  pair = std::pair<SDL_Texture *, SDL_Rect>(create_texture(name, name + ".png"), temp_rect);
  textureMap.insert(std::make_pair(name, pair));

  name = "battery";
  temp_rect = {790, 68, 31, 15};
  pair = std::pair<SDL_Texture *, SDL_Rect>(create_texture(name, name + ".png"), temp_rect);
  textureMap.insert(std::make_pair(name, pair));

  // avatar & hb menu
  name = "avatar";
  temp_rect = {60, 40, 60, 60};
  pair = std::pair<SDL_Texture *, SDL_Rect>(create_texture(name, name + ".png"), temp_rect);
  textureMap.insert(std::make_pair(name, pair));

  name = "hb_menu";
  temp_rect = {140, 40, 60, 60};
  pair = std::pair<SDL_Texture *, SDL_Rect>(create_texture("hb_menu", name + ".png"), temp_rect);
  textureMap.insert(std::make_pair(name, pair));
  // game info

  name = "company_bg";
  temp_rect = {0, 284, 640, 50};
  pair = std::pair<SDL_Texture *, SDL_Rect>(create_texture(name, name + ".png"), temp_rect);
  textureMap.insert(std::make_pair(name, pair));

  name = "gamename_bg";
  temp_rect = {0, 254, 640, 50};
  pair = std::pair<SDL_Texture *, SDL_Rect>(create_texture(name, name + ".png"), temp_rect);
  textureMap.insert(std::make_pair(name, pair));

  name = "selected_cursor";
  temp_rect = {455, 325, 350, 350};
  pair = std::pair<SDL_Texture *, SDL_Rect>(create_texture(name, "selected.png"), temp_rect);
  textureMap.insert(std::make_pair(name, pair));
}

void homescreen::update(std::vector<Title> titles, std::unordered_map<u64, SDL_Texture *> icons)
{
  /**
  std::pair<SDL_Texture*, SDL_Rect> p = textureMap.find("wallpaper")->second;
  SDL_Texture *t = p.first;
  SDL_Rect r = p.second;
  **/

  // gif wallpaper test

  CEV_gifAnimAuto(animation);
  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, actTexture, NULL, &blitPos);
  SDL_RenderPresent(renderer);

  //SDL_RenderCopy(renderer, t, NULL, &r);
  draw_top_menu();
  draw_games(titles, icons);
  draw_icons_menu();
  draw_seperators();
  draw_top_left();
  draw_details();
}

void homescreen::draw_top_menu()
{
  std::pair<SDL_Texture *, SDL_Rect> p = textureMap.find("top_bg")->second;
  SDL_Texture *t = p.first;
  SDL_Rect r = p.second;
  SDL_RenderCopy(renderer, t, NULL, &r);
  p = textureMap.find("handheld")->second;
  t = p.first;
  r = p.second;
  SDL_RenderCopy(renderer, t, NULL, &r);
  p = textureMap.find("wifi")->second;
  t = p.first;
  r = p.second;
  SDL_RenderCopy(renderer, t, NULL, &r);
  p = textureMap.find("battery")->second;
  t = p.first;
  r = p.second;
  SDL_RenderCopy(renderer, t, NULL, &r);
}

void homescreen::draw_icons_menu()
{
  std::pair<SDL_Texture *, SDL_Rect> p = textureMap.find("icons_bg")->second;
  SDL_Texture *t = p.first;
  SDL_Rect r = p.second;
  SDL_RenderCopy(renderer, t, NULL, &r);
  p = textureMap.find("news")->second;
  t = p.first;
  r = p.second;
  SDL_RenderCopy(renderer, t, NULL, &r);
  p = textureMap.find("e_shop")->second;
  t = p.first;
  r = p.second;
  SDL_RenderCopy(renderer, t, NULL, &r);
  p = textureMap.find("album")->second;
  t = p.first;
  r = p.second;
  SDL_RenderCopy(renderer, t, NULL, &r);
  p = textureMap.find("controller")->second;
  t = p.first;
  r = p.second;
  SDL_RenderCopy(renderer, t, NULL, &r);
  p = textureMap.find("settings")->second;
  t = p.first;
  r = p.second;
  SDL_RenderCopy(renderer, t, NULL, &r);
  p = textureMap.find("power")->second;
  t = p.first;
  r = p.second;
  SDL_RenderCopy(renderer, t, NULL, &r);
}

void homescreen::draw_top_left()
{
  std::pair<SDL_Texture *, SDL_Rect> p = textureMap.find("avatar")->second;
  SDL_Texture *t = p.first;
  SDL_Rect r = p.second;
  SDL_RenderCopy(renderer, t, NULL, &r);
  p = textureMap.find("hb_menu")->second;
  t = p.first;
  r = p.second;
  SDL_RenderCopy(renderer, t, NULL, &r);
}

void homescreen::draw_seperators()
{
  std::pair<SDL_Texture *, SDL_Rect> p = textureMap.find("seperator")->second;
  SDL_Texture *t = p.first;
  SDL_Rect r = p.second;
  SDL_RenderCopy(renderer, t, NULL, &r);
  p = textureMap.find("seperator2")->second;
  t = p.first;
  r = p.second;
  SDL_RenderCopy(renderer, t, NULL, &r);
  p = textureMap.find("seperator3")->second;
  t = p.first;
  r = p.second;
  SDL_RenderCopy(renderer, t, NULL, &r);
  p = textureMap.find("seperator4")->second;
  t = p.first;
  r = p.second;
  SDL_RenderCopy(renderer, t, NULL, &r);
  p = textureMap.find("seperator5")->second;
  t = p.first;
  r = p.second;
  SDL_RenderCopy(renderer, t, NULL, &r);
}

void homescreen::draw_details()
{
  std::pair<SDL_Texture *, SDL_Rect> p = textureMap.find("company_bg")->second;
  SDL_Texture *t = p.first;
  SDL_Rect r = {0, 284, 640, 50};
  r.x = game_info_text_pos.x - 20;
  SDL_RenderCopy(renderer, t, NULL, &r);
  p = textureMap.find("gamename_bg")->second;
  t = p.first;
  r = {0, 254, 640, 50};
  r.x = game_title_text_pos.x - 20;
  SDL_RenderCopy(renderer, t, NULL, &r);
}

void homescreen::draw_games(std::vector<Title> titles, std::unordered_map<u64, SDL_Texture *> icons)
{

  // draw selected game
  //auto it = std::next(titles.begin(), selected);
  SDL_Texture *t = icons.find(titles[selected].TitleID)->second;
  SDL_Rect r = {470, 340, 320, 320};
  SDL_RenderCopy(renderer, t, NULL, &r);

  SDL_Texture *selected_tex = textureMap.find("selected_cursor")->second.first;
  SDL_Rect selected_rect = textureMap.find("selected_cursor")->second.second;
  SDL_RenderCopy(renderer, selected_tex, NULL, &selected_rect);

  // loop through all games to the left of it and draw them to correct positions
  SDL_Rect temp_rect = {470 - 260 - 40, 400, 260, 260};
  if (selected != 0)
  {
    for (auto i = selected - 1; i >= 0; i--)
    {
      SDL_Texture *t = icons.find(titles[i].TitleID)->second;
      SDL_RenderCopy(renderer, t, NULL, &temp_rect);
      temp_rect.x -= 260 + 20; // icon size plus margin
    }
  }

  // loop through all games to the right of it and draw them to correct positions

  temp_rect = {470 + 320 + 40, 400, 260, 260};
  if (selected != titles.size() - 1)
  {
    for (auto i = selected + 1; i < titles.size(); i++)
    {
      SDL_Texture *t = icons.find(titles[i].TitleID)->second;
      SDL_RenderCopy(renderer, t, NULL, &temp_rect);
      temp_rect.x += 260 + 20; // icon size plus margin
    }
  }
}
