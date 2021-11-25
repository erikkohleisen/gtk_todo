imports.gi.versions['Gtk'] = '4.0';
const Gtk = imports.gi.Gtk;

let app = new Gtk.Application({ application_id: 'com.github.erikkohleisen.mytodoapp' });

app.connect('activate', () => {
    let win = new Gtk.ApplicationWindow({ application: app });
    win.set_title('My TODO App');
    win.set_default_size(600, 700);

    let box = new Gtk.Box({ orientation: 1 });
    box.set_spacing(10);
    box.set_valign(1); //start = 1
    box.set_halign(3); //center = 3
    win.set_child(box);

    let grid = new Gtk.Grid();
    grid.set_column_spacing(10);
    grid.set_margin_top(10);
    box.append(grid);

    let separator = new Gtk.Separator({ orientation: 1 });
    box.append(separator);

    let list = new Gtk.ListBox();
    list.set_show_separators(true);
    let label = new Gtk.Label({ label: 'TODO list will be displayed here' });
    list.set_placeholder(label);

    box.append(list);
    
    let buffer = new Gtk.EntryBuffer();
    let input = new Gtk.Entry(buffer);
    input.placeholder_text = 'Todo';

    let btn = new Gtk.Button({ label: 'Add' });

    btn.connect('clicked', () => {
        if (input.text === '') return;
        let row = new Gtk.ListBoxRow();
        let rowLabel = new Gtk.Label({ label: input.text });
        row.set_child(rowLabel);
        list.append(row);
        input.set_text('');
    });

    input.connect('activate', () => {
        if (input.text === '') return;
        let row = new Gtk.ListBoxRow();
        let rowLabel = new Gtk.Label({ label: input.text });
        row.set_child(rowLabel);
        list.append(row);
        input.set_text('');
    });

    list.connect('row-activated', () => {
        let row = list.get_selected_row();
        list.remove(row);
    });
     
    grid.attach(input, 0, 0, 1, 1);
    grid.attach(btn, 1, 0, 1, 1);

    win.present();
});

app.run([]);