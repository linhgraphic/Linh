////////////////////////////////////////////////////////////////////////////////
//
// (C) Andy Thomason 2012-2014
//
// Modular Framework for OpenGLES2 rendering on multiple platforms.
//
// Mesh smooth modifier. Work in progress.
//

namespace octet { namespace scene {
  /// Box mesh. Generate triangles for an AABB.
  class mesh_box : public mesh {
    mat4t transform;

    void init(aabb_in size, mat4t_in transform = mat4t())
    {
      this->transform = transform;
      set_default_attributes();
      set_aabb(size);
      update();
    }

  public:
    RESOURCE_META(mesh_box)

    /// Default constructor: 1x1x1
    mesh_box() {
      init(aabb(vec3(0, 0, 0), vec3(1, 1, 1)));
    }

    /// Construct box from size
    mesh_box(vec3_in size, mat4t_in transform=mat4t()) {
      init(aabb(vec3(0, 0, 0), size), transform);
    }

    void set_size(vec3_in size, mat4t_in transform=mat4t()) {
      init(aabb(vec3(0, 0, 0), size), transform);
      update();
    }

    /// Generate mesh from parameters.
    virtual void update() {
      aabb aabb_ = get_aabb();
      mesh::set_shape<math::aabb, mesh::vertex>(aabb_, transform, 1);
    }

    /// Serialise the box
    void visit(visitor &v) {
      mesh::visit(v);
      if (v.is_reader()) {
        update();
      }
    }
  };
}}

