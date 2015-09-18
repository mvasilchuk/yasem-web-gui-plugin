// Generated by CoffeeScript 1.9.1
(function() {
  var DEVICE_IMAGES, Main;

  DEVICE_IMAGES = {
    MAG_GENERIC: '../img/mag-generic.png',
    MAG_250: '../img/mag-250.png',
    MAG_255: '../img/mag-255.png',
    AURA_HD: '../img/aura-hd.png',
    DUNE_HD_102: '../img/dune-hd-102.png'
  };

  Main = (function() {
    var Menu, PAGE_IDENT, STORAGE_CURRENT_ITEM_ID, STORAGE_CURRENT_MENU, _createNode, appInfo, by_id, central_item_index, items_visible, menu_container, menu_outer_container, menu_position, menu_size, menu_stack, menu_visual_type, page_stack, page_state;

    function Main() {}

    STORAGE_CURRENT_MENU = 'current_menu';

    STORAGE_CURRENT_ITEM_ID = 'current_item_id';

    appInfo = {};

    menu_container = null;

    menu_outer_container = null;

    PAGE_IDENT = {
      MENU: "menu",
      PROFILE_CONFIG: "profile-configuration",
      HELP: "help"
    };

    menu_stack = [];

    page_stack = [];

    central_item_index = 0;

    page_state = PAGE_IDENT.MENU;

    items_visible = 5;

    menu_visual_type = null;

    menu_size = {
      width: 5,
      height: 3
    };

    menu_position = {
      x: 0,
      y: 0
    };

    Menu = {};

    by_id = function(id) {
      return document.getElementById(id);
    };

    _createNode = function(tag, jsonData, children) {
      var child, data_value, i, id, item, len, node, text, value;
      node = document.createElement(tag);
      if (tag === 'img') {
        node.onerror = function() {
          return this.style.display = 'none';
        };
      }
      for (id in jsonData) {
        data_value = jsonData[id];
        if (data_value === null) {
          continue;
        }
        switch (id) {
          case 'value':
            if (['label'].indexOf(tag) !== -1) {
              node.innerHTML = data_value;
            } else {
              node.value = data_value;
            }
            break;
          case 'text':
            node.innerHTML = data_value;
            break;
          case 'options':
            for (value in data_value) {
              text = data_value[value];
              item = _createNode('option', {
                value: value,
                text: text
              });
              if (value === jsonData.value) {
                item.selected = 'selected';
              }
              node.appendChild(item);
            }
            break;
          default:
            node.setAttribute(id, data_value);
        }
      }
      children = children || [];
      for (i = 0, len = children.length; i < len; i++) {
        child = children[i];
        node.appendChild(child);
      }
      return node;
    };

    Main.prototype.load = function() {
      console.log('Loading...');
      this.load_app_info();
      this.open_page(PAGE_IDENT.MENU);
      this.load_menu();
      this.prepare_menu();
      this.select_menu_item(0, 0);
      this.show_shortcuts_for_current_page();
      document.body.focus();
      return console.log('Loading finished');
    };

    Main.prototype.load_app_info = function() {
      this.appInfo = JSON.parse(__GUI__.getAppInfo());
      by_id('app-copyright').innerHTML = this.appInfo.copyright;
      return by_id('app-version').innerHTML = this.appInfo.version;
    };

    Main.prototype.load_menu = function() {
      if (typeof __GUI__ !== "undefined" && __GUI__ !== null) {
        Menu = JSON.parse(__GUI__.makeJsonMenu());
        console.log(Menu);
      }
      if (!Menu.items[Menu.current].count) {
        console.error('Menu is either empty or items count not set');
      }
      items_visible = Menu.items[Menu.current].count > items_visible ? items_visible : Menu.items[Menu.current].count;
      return central_item_index = Math.floor(items_visible / 2);
    };

    Main.prototype.clear_menu = function() {
      var results;
      menu_outer_container = document.getElementById('menu');
      menu_container = document.getElementById('main-menu');
      results = [];
      while (menu_container.hasChildNodes()) {
        results.push(menu_container.removeChild(menu_container.firstChild));
      }
      return results;
    };


    /**
    #*
    #* @param {string?} menu_name
    *
     */

    Main.prototype.prepare_menu = function(menu_name) {
      var child_mark, dev_image, id, image, img, item, menu, node, onclick, onmouseover, parent_mark, ref, results, self, title;
      this.clear_menu();
      if (typeof menu_name !== 'undefined') {
        Menu.current = menu_name;
      }
      console.log('current menu: ' + Menu.current);
      if (typeof Menu.items[Menu.current].items !== 'object') {
        console.error("Menu items not found! Did you forget to add 'items' into menu object?");
        return false;
      }

      /**
       1 = Left   mouse button
       2 = Centre mouse button
       3 = Right  mouse button
       *
       */
      self = this;
      onclick = function(e) {
        console.log('click:' + e);
        if (e.which === 1) {
          return self.onkeydown({
            keyCode: KEY_CODE.ENTER,
            '$item': this.id
          });
        }
      };
      onmouseover = function(e) {
        var coord;
        coord = self.find_menu_item_by_id(this.id);
        return self.select_menu_item(coord.x, coord.y);
      };
      ref = Menu.items[Menu.current].items;
      results = [];
      for (id in ref) {
        item = ref[id];
        menu = Menu.items[Menu.current].items[id];
        node = _createNode('div', {
          'class': 'item',
          'id': id
        });
        image = _createNode('div', {
          'class': 'image'
        });
        console.log(menu["class"] + ':' + menu.submodel);
        dev_image = menu.image;
        switch (menu["class"]) {
          case 'mag':
            switch (menu.submodel) {
              case 'MAG250':
                dev_image = DEVICE_IMAGES.MAG_250;
                break;
              case 'MAG255':
                dev_image = DEVICE_IMAGES.MAG_255;
                break;
              case 'AuraHD':
                dev_image = DEVICE_IMAGES.AURA_HD;
                break;
              default:
                dev_image = DEVICE_IMAGES.MAG_GENERIC;
                break;
            }
            break;
          case 'dunehd':
            switch (menu.submodel) {
              case 'Dune HD TV-102':
                dev_image = DEVICE_IMAGES.DUNE_HD_102;
                break;
            }
            break;
          default:
            break;
        }
        img = _createNode('img', {
          'src': dev_image
        });
        image.appendChild(img);
        title = _createNode('div', {
          'class': 'title',
          'text': menu.title
        });
        node.appendChild(image);
        node.appendChild(title);
        node.addEventListener('click', onclick);
        node.addEventListener('mouseover', onmouseover);
        if (typeof menu.submenu === 'string') {
          parent_mark = _createNode('div', {
            'class': 'parent_mark'
          });
          node.appendChild(parent_mark);
        }
        if (typeof Menu.items[Menu.current].parent_menu === 'string') {
          child_mark = _createNode('div', {
            'class': 'child_mark'
          });
          node.appendChild(child_mark);
        }
        results.push(menu_container.appendChild(node));
      }
      return results;
    };


    /**
     *
     * @param {Event|object} e
     *
     */

    Main.prototype.onkeydown = function(e) {
      var preventDefault;
      preventDefault = false;
      switch (page_state) {
        case PAGE_IDENT.MENU:
          preventDefault = this.on_menu_keydown(e);
          break;
        case PAGE_IDENT.PROFILE_CONFIG:
          preventDefault = this.on_profile_config_keydown(e, true);
          break;
        case PAGE_IDENT.HELP:
          preventDefault = this.on_help_keydown(e, true);
          break;
        default:
          console.warn('No key handler for page state', page_state);
      }
      if (preventDefault && e.preventDefault) {
        return e.preventDefault();
      }
    };


    /**
     *
     * @param {Event} e
     *
     */

    Main.prototype.on_menu_keydown = function(e) {

      /*
          If clicked on menu item then item's ID is in e.$item
       */
      var menu, menu_id, submenu;
      menu_id = e.$item ? e.$item : menu_id = Menu.current_item_id;
      menu = Menu.items[Menu.current].items[menu_id];
      console.log('Menu:', menu);
      switch (e.keyCode) {
        case KEY_CODE.LEFT:
          this.select_menu_item(menu_position.x - 1, menu_position.y);
          break;
        case KEY_CODE.TOP:
          this.select_menu_item(menu_position.x, menu_position.y - 1);
          break;
        case KEY_CODE.RIGHT:
          this.select_menu_item(menu_position.x + 1, menu_position.y);
          break;
        case KEY_CODE.DOWN:
          this.select_menu_item(menu_position.x, menu_position.y + 1);
          break;
        case KEY_CODE.ENTER:
          if (menu.type === MENU_TYPE.PROFILE) {
            __GUI__.loadProfile(menu.id);
          }
          if (menu.type === MENU_TYPE.NEW_PROFILE) {
            this.create_new_profile(menu["class"], menu.submodel, "{}");
          } else if (typeof menu.submenu !== 'undefined') {
            submenu = menu.submenu;
            menu_stack.push(Menu.current);
            Menu.items[submenu].parent_menu = Menu.current;
            this.prepare_menu(submenu);
          }
          break;
        case KEY_CODE.ESC:
          if (menu_stack.length > 0) {
            this.prepare_menu(menu_stack.pop());
          } else {
            console.warn('No menu in stack!');
          }
          break;
        case KEY_CODE.KEY_CODE_F1:
          this.open_page(PAGE_IDENT.HELP);
          break;
        case KEY_CODE.KEY_CODE_F2:
          this.load_profile_config(Menu.current_item_id);
          break;
        case KEY_CODE.KEY_CODE_F3:
          console.log("F3");
          break;
        case KEY_CODE.KEY_CODE_F4:
          if (confirm('Remove profile ' + menu.title + '?')) {
            __GUI__.removeProfile(Menu.current_item_id);
            document.location.reload();
          }
          break;
        default:
          return false;
      }
      return true;
    };


    /**
     *
     * @param {Event} e
     *
     */

    Main.prototype.on_profile_config_keydown = function(e) {
      switch (e.keyCode) {
        case KEY_CODE.KEY_CODE_F1:
          console.log("F1");
          break;
        case KEY_CODE.KEY_CODE_F2:
          console.log("F2");
          this.save_profile_config();
          break;
        case KEY_CODE.KEY_CODE_F3:
          console.log("F3");
          break;
        case KEY_CODE.KEY_CODE_F4:
          console.log("F4");
          break;
        case KEY_CODE.ESC:
          this.close_page();
          break;
        default:
          return false;
      }
      return true;
    };


    /**
     *
     * @param {Event} e
     *
     */

    Main.prototype.on_help_keydown = function(e) {
      switch (e.keyCode) {
        case KEY_CODE.ESC:
          this.close_page();
          break;
        default:
          return false;
      }
      return true;
    };

    Main.prototype.move_menu_blocks = function(offset) {
      var element, elements, i, id, index, item, len, ref, results;
      elements = document.getElementsByClassName('item');
      for (index = i = 0, len = elements.length; i < len; index = ++i) {
        element = elements[index];
        element.className = 'item';
      }
      index = 0;
      ref = Menu.items[Menu.current].items;
      results = [];
      for (id in ref) {
        item = ref[id];
        if (index === offset) {
          element = document.getElementById(id);
          element.className += ' selected';
          Menu.current_item_id = element.id;
          break;
        }
        results.push(index++);
      }
      return results;
    };

    Main.prototype.find_menu_item_by_id = function(id) {
      var element, elements, i, index, len;
      elements = document.getElementsByClassName('item');
      for (index = i = 0, len = elements.length; i < len; index = ++i) {
        element = elements[index];
        if (element.id === id) {
          return {
            x: index % menu_size.width,
            y: Math.floor(index / menu_size.width)
          };
        }
      }
      return null;
    };

    Main.prototype.select_menu_item = function(x, y) {
      var menu_item_count, row_count;
      menu_item_count = Menu.items[Menu.current].count;
      row_count = Math.floor(menu_item_count / menu_size.width) + 1;
      if (x >= menu_size.width) {
        x = x - menu_size.width;
        y++;
      }
      if (x < 0) {
        x = menu_size.width + x;
        y--;
      }
      if (y >= row_count) {
        y = y - row_count;
      }
      if (y < 0) {
        y = row_count + y;
      }
      if ((x + 1) * (y + 1) >= menu_size.width * row_count) {
        x = 0;
        y = 0;
      }
      if (x + (y * menu_size.width) >= menu_item_count) {
        y = Math.floor(menu_item_count / menu_size.width);
        x = menu_item_count - y * menu_size.width - 1;
      }
      menu_position.x = x;
      menu_position.y = y;
      return this.move_menu_blocks(x + menu_size.width * y);
    };

    Main.prototype.create_new_profile = function(class_id, submodel, data) {
      var id;
      id = __GUI__.createProfile(class_id, submodel, data);
      return this.load_profile_config(id);
    };

    Main.prototype.save_profile_config = function() {
      var data, element, elements, i, index, len, name;
      data = [];
      elements = document.getElementsByClassName('config-option');
      for (index = i = 0, len = elements.length; i < len; index = ++i) {
        element = elements[index];
        console.log('el', element.id, element.value);
        name = /^config-(.*?)$/.exec(element.id)[1];
        if (name === null) {
          console.log('name:' + name);
          continue;
        }
        console.log('name', name);
        data.push({
          name: name,
          value: element.value
        });
      }
      __GUI__.saveProfile(this.profile_id, JSON.stringify(data));
      return document.location.reload();
    };


    /**
    * @param {string} profile_id
    * @param {string} class_id?
    *
     */

    Main.prototype.load_profile_config = function(profile_id, class_id) {
      var _comment, config, config_data, config_item, config_table, edit_tag_id, elemTag, i, index, inputType, len, new_node_options, options, results, submodel_key, tr;
      this.open_page(PAGE_IDENT.PROFILE_CONFIG);
      this.profile_id = profile_id;
      config = null;
      config_data = JSON.parse(__GUI__.getProfileConfigOptions(this.profile_id));
      submodel_key = config_data['submodel_key'];
      config = config_data.options;
      config_table = document.getElementById('config-container');
      while (config_table.hasChildNodes()) {
        config_table.removeChild(config_table.firstChild);
      }
      results = [];
      for (index = i = 0, len = config.length; i < len; index = ++i) {
        config_item = config[index];
        config_item = config[index];
        elemTag = null;
        inputType = null;
        options = null;
        switch (config_item.type) {
          case CONFIG_ITEM_TYPES.STRING:
          case CONFIG_ITEM_TYPES.INT:
            elemTag = 'input';
            break;
          case CONFIG_ITEM_TYPES.BOOL:
            elemTag = 'select';
            options = {
              'true': 'TRUE',
              'false': 'FALSE'
            };
            break;
          default:
            console.log('options' + typeof config_item.options);
            if (typeof config_item.options !== 'undefined' && config_item.options) {
              elemTag = 'select';
              options = config_item.options;
            } else {
              elemTag = 'input';
            }
            break;
        }
        edit_tag_id = 'config-' + config_item.tag + '/' + config_item.name;
        new_node_options = [
          _createNode('td', {}, [
            _createNode('label', {
              'value': config_item.title,
              'for': edit_tag_id
            })
          ]), _createNode('td', {}, [
            _createNode(elemTag, {
              value: config_item.value,
              "class": 'config-option',
              id: edit_tag_id,
              type: inputType,
              options: options
            })
          ])
        ];
        tr = _createNode('tr', {
          'class': 'config-row'
        }, new_node_options);
        config_table.appendChild(tr);
        if (typeof config_item.comment !== 'undefined') {
          _comment = _createNode('tr', {
            "class": 'comment'
          }, [
            _createNode('td', {
              colspan: 2
            }, [
              _createNode('span', {
                "class": 'text',
                text: config_item.comment
              })
            ])
          ]);
          results.push(config_table.appendChild(_comment));
        } else {
          results.push(void 0);
        }
      }
      return results;
    };


    /**
    *
    * @param {boolean} show
    *
     */

    Main.prototype.show_shortcuts = function(show) {
      var shortcuts;
      shortcuts = document.getElementById('shortcuts');
      return shortcuts.className = show ? '' : 'hidden';
    };

    Main.prototype.show_shortcuts_for_current_page = function() {
      switch (page_state) {
        case PAGE_IDENT.MENU:
          return this.set_shortcuts([
            {
              id: 'ESC',
              text: 'NONE'
            }, {
              id: 'F1',
              text: 'Help'
            }, {
              id: 'F2',
              text: 'Edit profile'
            }, {
              id: 'F4',
              text: 'Remove profile'
            }
          ]);
        case PAGE_IDENT.PROFILE_CONFIG:
          return this.set_shortcuts([
            {
              id: 'ESC',
              text: 'Return'
            }, {
              id: 'F2',
              text: 'Save profile'
            }
          ]);
        case PAGE_IDENT.HELP:
          return this.set_shortcuts([
            {
              id: 'ESC',
              text: 'Return'
            }
          ]);
        default:
          return this.set_shortcuts([]);
      }
    };

    Main.prototype.set_shortcuts = function(data) {
      var i, item, len, shortcut, shortcuts;
      shortcuts = document.getElementById('shortcuts');
      while (shortcuts.hasChildNodes()) {
        shortcuts.removeChild(shortcuts.firstChild);
      }
      for (i = 0, len = data.length; i < len; i++) {
        item = data[i];
        shortcut = _createNode('div', {
          "class": 'shortcut',
          'data-id': item.id
        }, [
          _createNode('span', {
            "class": 'key ' + item.id,
            text: item.id
          }), _createNode('span', {
            "class": 'title',
            text: item.text
          })
        ]);
        shortcuts.appendChild(shortcut);
      }
    };

    Main.prototype.close_page = function() {
      var container, last_page, this_page;
      console.log(page_stack);
      if (page_stack.size < 2) {
        return;
      }
      this_page = page_stack.pop();
      last_page = page_stack[page_stack.length - 1];
      console.log(this_page, last_page);
      container = document.getElementById(this_page.id);
      container.className = 'page hidden';
      page_state = last_page.page_state;
      return this.show_shortcuts_for_current_page();
    };

    Main.prototype.open_page = function(id) {
      var container;
      page_state = null;
      container = document.getElementById(id);
      if (!container) {
        console.error('Page ID not found', id);
        return;
      }
      switch (id) {
        case "menu":
          page_state = PAGE_IDENT.MENU;
          break;
        case "profile-configuration":
          page_state = PAGE_IDENT.PROFILE_CONFIG;
          break;
        case "help":
          page_state = PAGE_IDENT.HELP;
          break;
        default:
          console.log('Undefined page', id);
      }
      container.className = 'page top';
      page_stack.push({
        id: id,
        page_state: page_state
      });
      return this.show_shortcuts_for_current_page();
    };

    return Main;

  })();

  window.Main = new Main();

}).call(this);
