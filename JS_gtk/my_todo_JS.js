imports.gi.versions['Gtk'] = '4.0';
const Gtk = imports.gi.Gtk;

let app = new Gtk.Application({ application_id: 'com.github.erikkohleisen.mytodoapp' });

/*const cbObject = {
    'buffer': null,
    'list': null
}*/

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
    let label = new Gtk.Label();
    label.set_text('TODO list will be displayed here');
    list.set_placeholder(label);

    box.append(list);
    
    let buffer = new Gtk.EntryBuffer();
    let input = new Gtk.Entry(buffer);
    input.placeholder_text = 'Todo';

    let cbObject = {
        'buffer': buffer,
        'list': list
    }

    let btn = new Gtk.Button({ label: 'Add' });
    btn.connect('clicked', (cbObject) => {
        let row = new Gtk.ListBoxRow();
        let rowLabel = new Gtk.Label();
        rowLabel.set_text(cbObject.buffer.get_text());
        row.set_child(rowLabel);
        cbObject.list.append(row);
        cbObject.buffer.delete_text(0, -1);
    });
     
    grid.attach(input, 0, 0, 1, 1);
    grid.attach(btn, 1, 0, 1, 1);

    win.present();
});

app.run([]);